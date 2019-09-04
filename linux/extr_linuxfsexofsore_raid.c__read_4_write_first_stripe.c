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
typedef  unsigned int u64 ;
struct page {int dummy; } ;
struct ore_striping_info {unsigned int obj_offset; } ;
struct TYPE_3__ {unsigned int first_stripe_start; } ;
struct ore_io_state {unsigned int offset; int /*<<< orphan*/  private; TYPE_2__* r4w; int /*<<< orphan*/  layout; TYPE_1__ si; struct __stripe_pages_2d* sp2d; } ;
struct __stripe_pages_2d {unsigned int pages_in_unit; struct __1_page_stripe* _1p_stripes; } ;
struct __1_page_stripe {int* page_is_read; struct page** pages; } ;
struct TYPE_4__ {struct page* (* get_page ) (int /*<<< orphan*/ ,unsigned int,int*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ORE_DBGMSG (char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  _add_to_r4w (struct ore_io_state*,struct ore_striping_info*,struct page*,unsigned int) ; 
 int /*<<< orphan*/  _add_to_r4w_first_page (struct ore_io_state*,struct page*) ; 
 unsigned int _sp2d_max_pg (struct __stripe_pages_2d*) ; 
 unsigned int _sp2d_min_pg (struct __stripe_pages_2d*) ; 
 int /*<<< orphan*/  ore_calc_stripe_info (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct ore_striping_info*) ; 
 struct page* stub1 (int /*<<< orphan*/ ,unsigned int,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int _read_4_write_first_stripe(struct ore_io_state *ios)
{
	struct ore_striping_info read_si;
	struct __stripe_pages_2d *sp2d = ios->sp2d;
	u64 offset = ios->si.first_stripe_start;
	unsigned c, p, min_p = sp2d->pages_in_unit, max_p = -1;

	if (offset == ios->offset) /* Go to start collect $200 */
		goto read_last_stripe;

	min_p = _sp2d_min_pg(sp2d);
	max_p = _sp2d_max_pg(sp2d);

	ORE_DBGMSG("stripe_start=0x%llx ios->offset=0x%llx min_p=%d max_p=%d\n",
		   offset, ios->offset, min_p, max_p);

	for (c = 0; ; c++) {
		ore_calc_stripe_info(ios->layout, offset, 0, &read_si);
		read_si.obj_offset += min_p * PAGE_SIZE;
		offset += min_p * PAGE_SIZE;
		for (p = min_p; p <= max_p; p++) {
			struct __1_page_stripe *_1ps = &sp2d->_1p_stripes[p];
			struct page **pp = &_1ps->pages[c];
			bool uptodate;

			if (*pp) {
				if (ios->offset % PAGE_SIZE)
					/* Read the remainder of the page */
					_add_to_r4w_first_page(ios, *pp);
				/* to-be-written pages start here */
				goto read_last_stripe;
			}

			*pp = ios->r4w->get_page(ios->private, offset,
						 &uptodate);
			if (unlikely(!*pp))
				return -ENOMEM;

			if (!uptodate)
				_add_to_r4w(ios, &read_si, *pp, PAGE_SIZE);

			/* Mark read-pages to be cache_released */
			_1ps->page_is_read[c] = true;
			read_si.obj_offset += PAGE_SIZE;
			offset += PAGE_SIZE;
		}
		offset += (sp2d->pages_in_unit - p) * PAGE_SIZE;
	}

read_last_stripe:
	return 0;
}