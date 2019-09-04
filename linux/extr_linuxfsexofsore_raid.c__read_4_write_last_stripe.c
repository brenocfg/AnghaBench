#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct page {int dummy; } ;
struct ore_striping_info {unsigned int cur_pg; unsigned int cur_comp; int obj_offset; } ;
struct TYPE_3__ {unsigned int bytes_in_stripe; } ;
struct ore_io_state {int offset; int length; int /*<<< orphan*/  layout; int /*<<< orphan*/  private; TYPE_2__* r4w; TYPE_1__ si; struct __stripe_pages_2d* sp2d; } ;
struct __stripe_pages_2d {unsigned int pages_in_unit; struct __1_page_stripe* _1p_stripes; } ;
struct __1_page_stripe {int* page_is_read; struct page** pages; } ;
struct TYPE_4__ {struct page* (* get_page ) (int /*<<< orphan*/ ,int,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct page*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ORE_DBGMSG (char*,int,int,unsigned int,unsigned int) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  _add_to_r4w (struct ore_io_state*,struct ore_striping_info*,struct page*,int) ; 
 int /*<<< orphan*/  _add_to_r4w_last_page (struct ore_io_state*,int*) ; 
 unsigned int _sp2d_max_pg (struct __stripe_pages_2d*) ; 
 unsigned int _sp2d_min_pg (struct __stripe_pages_2d*) ; 
 unsigned int div_u64 (int,unsigned int) ; 
 int /*<<< orphan*/  ore_calc_stripe_info (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ore_striping_info*) ; 
 struct page* stub1 (int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int _read_4_write_last_stripe(struct ore_io_state *ios)
{
	struct ore_striping_info read_si;
	struct __stripe_pages_2d *sp2d = ios->sp2d;
	u64 offset;
	u64 last_stripe_end;
	unsigned bytes_in_stripe = ios->si.bytes_in_stripe;
	unsigned c, p, min_p = sp2d->pages_in_unit, max_p = -1;

	offset = ios->offset + ios->length;
	if (offset % PAGE_SIZE)
		_add_to_r4w_last_page(ios, &offset);
		/* offset will be aligned to next page */

	last_stripe_end = div_u64(offset + bytes_in_stripe - 1, bytes_in_stripe)
				 * bytes_in_stripe;
	if (offset == last_stripe_end) /* Optimize for the aligned case */
		goto read_it;

	ore_calc_stripe_info(ios->layout, offset, 0, &read_si);
	p = read_si.cur_pg;
	c = read_si.cur_comp;

	if (min_p == sp2d->pages_in_unit) {
		/* Didn't do it yet */
		min_p = _sp2d_min_pg(sp2d);
		max_p = _sp2d_max_pg(sp2d);
	}

	ORE_DBGMSG("offset=0x%llx stripe_end=0x%llx min_p=%d max_p=%d\n",
		   offset, last_stripe_end, min_p, max_p);

	while (offset < last_stripe_end) {
		struct __1_page_stripe *_1ps = &sp2d->_1p_stripes[p];

		if ((min_p <= p) && (p <= max_p)) {
			struct page *page;
			bool uptodate;

			BUG_ON(_1ps->pages[c]);
			page = ios->r4w->get_page(ios->private, offset,
						  &uptodate);
			if (unlikely(!page))
				return -ENOMEM;

			_1ps->pages[c] = page;
			/* Mark read-pages to be cache_released */
			_1ps->page_is_read[c] = true;
			if (!uptodate)
				_add_to_r4w(ios, &read_si, page, PAGE_SIZE);
		}

		offset += PAGE_SIZE;
		if (p == (sp2d->pages_in_unit - 1)) {
			++c;
			p = 0;
			ore_calc_stripe_info(ios->layout, offset, 0, &read_si);
		} else {
			read_si.obj_offset += PAGE_SIZE;
			++p;
		}
	}

read_it:
	return 0;
}