#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct page {int dummy; } ;
struct ore_striping_info {unsigned int cur_pg; scalar_t__ cur_comp; } ;
struct ore_per_dev_state {scalar_t__ cur_sg; unsigned int offset; int /*<<< orphan*/  length; } ;
struct ore_io_state {scalar_t__ sgs_per_dev; int cur_par_page; int /*<<< orphan*/  private; int /*<<< orphan*/  r4w; struct page** parity_pages; struct __stripe_pages_2d* sp2d; scalar_t__ reading; } ;
struct __stripe_pages_2d {scalar_t__ data_devs; scalar_t__ pages_in_unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ORE_DBGMSG (char*,scalar_t__,scalar_t__) ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  _gen_xor_unit (struct __stripe_pages_2d*) ; 
 int /*<<< orphan*/  _ore_add_sg_seg (struct ore_per_dev_state*,unsigned int,int) ; 
 int _ore_add_stripe_unit (struct ore_io_state*,unsigned int*,int /*<<< orphan*/ ,struct page**,struct ore_per_dev_state*,unsigned int) ; 
 struct page* _raid_page_alloc () ; 
 int /*<<< orphan*/  _read_4_write_execute (struct ore_io_state*) ; 
 int /*<<< orphan*/  _read_4_write_first_stripe (struct ore_io_state*) ; 
 int /*<<< orphan*/  _read_4_write_last_stripe (struct ore_io_state*) ; 
 unsigned int _sp2d_max_pg (struct __stripe_pages_2d*) ; 
 unsigned int _sp2d_min_pg (struct __stripe_pages_2d*) ; 
 int /*<<< orphan*/  _sp2d_reset (struct __stripe_pages_2d*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int _ore_add_parity_unit(struct ore_io_state *ios,
			    struct ore_striping_info *si,
			    struct ore_per_dev_state *per_dev,
			    unsigned cur_len, bool do_xor)
{
	if (ios->reading) {
		if (per_dev->cur_sg >= ios->sgs_per_dev) {
			ORE_DBGMSG("cur_sg(%d) >= sgs_per_dev(%d)\n" ,
				per_dev->cur_sg, ios->sgs_per_dev);
			return -ENOMEM;
		}
		_ore_add_sg_seg(per_dev, cur_len, true);
	} else {
		struct __stripe_pages_2d *sp2d = ios->sp2d;
		struct page **pages = ios->parity_pages + ios->cur_par_page;
		unsigned num_pages;
		unsigned array_start = 0;
		unsigned i;
		int ret;

		si->cur_pg = _sp2d_min_pg(sp2d);
		num_pages  = _sp2d_max_pg(sp2d) + 1 - si->cur_pg;

		if (!per_dev->length) {
			per_dev->offset += si->cur_pg * PAGE_SIZE;
			/* If first stripe, Read in all read4write pages
			 * (if needed) before we calculate the first parity.
			 */
			if (do_xor)
				_read_4_write_first_stripe(ios);
		}
		if (!cur_len && do_xor)
			/* If last stripe r4w pages of last stripe */
			_read_4_write_last_stripe(ios);
		_read_4_write_execute(ios);

		for (i = 0; i < num_pages; i++) {
			pages[i] = _raid_page_alloc();
			if (unlikely(!pages[i]))
				return -ENOMEM;

			++(ios->cur_par_page);
		}

		BUG_ON(si->cur_comp < sp2d->data_devs);
		BUG_ON(si->cur_pg + num_pages > sp2d->pages_in_unit);

		ret = _ore_add_stripe_unit(ios,  &array_start, 0, pages,
					   per_dev, num_pages * PAGE_SIZE);
		if (unlikely(ret))
			return ret;

		if (do_xor) {
			_gen_xor_unit(sp2d);
			_sp2d_reset(sp2d, ios->r4w, ios->private);
		}
	}
	return 0;
}