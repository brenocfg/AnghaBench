#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ore_striping_info {unsigned int dev; scalar_t__ length; unsigned int par_dev; unsigned int unit_off; int cur_comp; scalar_t__ obj_offset; scalar_t__ cur_pg; } ;
struct ore_per_dev_state {unsigned int dev; scalar_t__ offset; int /*<<< orphan*/  length; } ;
struct ore_io_state {unsigned int pages_consumed; scalar_t__ length; unsigned int numdevs; unsigned int pgbase; TYPE_1__* layout; scalar_t__ sp2d; int /*<<< orphan*/  pages; struct ore_per_dev_state* per_dev; struct ore_striping_info si; } ;
struct TYPE_2__ {unsigned int stripe_unit; unsigned int mirrors_p1; unsigned int group_width; unsigned int parity; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int PAGE_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int _add_parity_units (struct ore_io_state*,struct ore_striping_info*,unsigned int,unsigned int,unsigned int,unsigned int,scalar_t__) ; 
 int _ore_add_stripe_unit (struct ore_io_state*,unsigned int*,unsigned int,int /*<<< orphan*/ ,struct ore_per_dev_state*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int _prepare_for_striping(struct ore_io_state *ios)
{
	struct ore_striping_info *si = &ios->si;
	unsigned stripe_unit = ios->layout->stripe_unit;
	unsigned mirrors_p1 = ios->layout->mirrors_p1;
	unsigned group_width = ios->layout->group_width;
	unsigned devs_in_group = group_width * mirrors_p1;
	unsigned dev = si->dev;
	unsigned first_dev = dev - (dev % devs_in_group);
	unsigned cur_pg = ios->pages_consumed;
	u64 length = ios->length;
	int ret = 0;

	if (!ios->pages) {
		ios->numdevs = ios->layout->mirrors_p1;
		return 0;
	}

	BUG_ON(length > si->length);

	while (length) {
		struct ore_per_dev_state *per_dev =
						&ios->per_dev[dev - first_dev];
		unsigned cur_len, page_off = 0;

		if (!per_dev->length && !per_dev->offset) {
			/* First time initialize the per_dev info. */
			per_dev->dev = dev;
			if (dev == si->dev) {
				WARN_ON(dev == si->par_dev);
				per_dev->offset = si->obj_offset;
				cur_len = stripe_unit - si->unit_off;
				page_off = si->unit_off & ~PAGE_MASK;
				BUG_ON(page_off && (page_off != ios->pgbase));
			} else {
				per_dev->offset = si->obj_offset - si->unit_off;
				cur_len = stripe_unit;
			}
		} else {
			cur_len = stripe_unit;
		}
		if (cur_len >= length)
			cur_len = length;

		ret = _ore_add_stripe_unit(ios, &cur_pg, page_off, ios->pages,
					   per_dev, cur_len);
		if (unlikely(ret))
			goto out;

		length -= cur_len;

		dev = ((dev + mirrors_p1) % devs_in_group) + first_dev;
		si->cur_comp = (si->cur_comp + 1) % group_width;
		if (unlikely((dev == si->par_dev) || (!length && ios->sp2d))) {
			if (!length && ios->sp2d) {
				/* If we are writing and this is the very last
				 * stripe. then operate on parity dev.
				 */
				dev = si->par_dev;
				/* If last stripe operate on parity comp */
				si->cur_comp = group_width - ios->layout->parity;
			}

			/* In writes cur_len just means if it's the
			 * last one. See _ore_add_parity_unit.
			 */
			ret = _add_parity_units(ios, si, dev, first_dev,
						mirrors_p1, devs_in_group,
						ios->sp2d ? length : cur_len);
			if (unlikely(ret))
					goto out;

			/* Rotate next par_dev backwards with wraping */
			si->par_dev = (devs_in_group + si->par_dev -
				       ios->layout->parity * mirrors_p1) %
				      devs_in_group + first_dev;
			/* Next stripe, start fresh */
			si->cur_comp = 0;
			si->cur_pg = 0;
			si->obj_offset += cur_len;
			si->unit_off = 0;
		}
	}
out:
	ios->numdevs = devs_in_group;
	ios->pages_consumed = cur_pg;
	return ret;
}