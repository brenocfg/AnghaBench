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
typedef  unsigned int u64 ;
typedef  scalar_t__ u32 ;
struct page {int dummy; } ;
struct ore_layout {unsigned int group_width; unsigned int mirrors_p1; unsigned int parity; unsigned int stripe_unit; } ;
struct TYPE_2__ {int length; } ;
struct ore_io_state {int reading; unsigned int offset; int length; int nr_pages; TYPE_1__ si; } ;
struct ore_components {int dummy; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int _ore_get_io_state (struct ore_layout*,struct ore_components*,unsigned int,unsigned int,unsigned int,struct ore_io_state**) ; 
 int /*<<< orphan*/  _ore_post_alloc_raid_stuff (struct ore_io_state*) ; 
 int div_u64 (unsigned int,unsigned int) ; 
 unsigned int div_u64_rem (unsigned int,unsigned int,scalar_t__*) ; 
 int /*<<< orphan*/  ore_calc_stripe_info (struct ore_layout*,unsigned int,unsigned int,TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

int  ore_get_rw_state(struct ore_layout *layout, struct ore_components *oc,
		      bool is_reading, u64 offset, u64 length,
		      struct ore_io_state **pios)
{
	struct ore_io_state *ios;
	unsigned numdevs = layout->group_width * layout->mirrors_p1;
	unsigned sgs_per_dev = 0, max_par_pages = 0;
	int ret;

	if (layout->parity && length) {
		unsigned data_devs = layout->group_width - layout->parity;
		unsigned stripe_size = layout->stripe_unit * data_devs;
		unsigned pages_in_unit = layout->stripe_unit / PAGE_SIZE;
		u32 remainder;
		u64 num_stripes;
		u64 num_raid_units;

		num_stripes = div_u64_rem(length, stripe_size, &remainder);
		if (remainder)
			++num_stripes;

		num_raid_units =  num_stripes * layout->parity;

		if (is_reading) {
			/* For reads add per_dev sglist array */
			/* TODO: Raid 6 we need twice more. Actually:
			*         num_stripes / LCMdP(W,P);
			*         if (W%P != 0) num_stripes *= parity;
			*/

			/* first/last seg is split */
			num_raid_units += layout->group_width;
			sgs_per_dev = div_u64(num_raid_units, data_devs) + 2;
		} else {
			/* For Writes add parity pages array. */
			max_par_pages = num_raid_units * pages_in_unit *
						sizeof(struct page *);
		}
	}

	ret = _ore_get_io_state(layout, oc, numdevs, sgs_per_dev, max_par_pages,
				pios);
	if (unlikely(ret))
		return ret;

	ios = *pios;
	ios->reading = is_reading;
	ios->offset = offset;

	if (length) {
		ore_calc_stripe_info(layout, offset, length, &ios->si);
		ios->length = ios->si.length;
		ios->nr_pages = ((ios->offset & (PAGE_SIZE - 1)) +
				 ios->length + PAGE_SIZE - 1) / PAGE_SIZE;
		if (layout->parity)
			_ore_post_alloc_raid_stuff(ios);
	}

	return 0;
}