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
struct ore_striping_info {int cur_comp; scalar_t__ unit_off; scalar_t__ obj_offset; } ;
struct ore_per_dev_state {unsigned int dev; scalar_t__ offset; int /*<<< orphan*/  length; } ;
struct ore_io_state {TYPE_1__* layout; struct ore_per_dev_state* per_dev; } ;
struct TYPE_2__ {unsigned int parity; int group_width; } ;

/* Variables and functions */
 int _ore_add_parity_unit (struct ore_io_state*,struct ore_striping_info*,struct ore_per_dev_state*,unsigned int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int _add_parity_units(struct ore_io_state *ios,
			     struct ore_striping_info *si,
			     unsigned dev, unsigned first_dev,
			     unsigned mirrors_p1, unsigned devs_in_group,
			     unsigned cur_len)
{
	unsigned do_parity;
	int ret = 0;

	for (do_parity = ios->layout->parity; do_parity; --do_parity) {
		struct ore_per_dev_state *per_dev;

		per_dev = &ios->per_dev[dev - first_dev];
		if (!per_dev->length && !per_dev->offset) {
			/* Only/always the parity unit of the first
			 * stripe will be empty. So this is a chance to
			 * initialize the per_dev info.
			 */
			per_dev->dev = dev;
			per_dev->offset = si->obj_offset - si->unit_off;
		}

		ret = _ore_add_parity_unit(ios, si, per_dev, cur_len,
					   do_parity == 1);
		if (unlikely(ret))
				break;

		if (do_parity != 1) {
			dev = ((dev + mirrors_p1) % devs_in_group) + first_dev;
			si->cur_comp = (si->cur_comp + 1) %
						       ios->layout->group_width;
		}
	}

	return ret;
}