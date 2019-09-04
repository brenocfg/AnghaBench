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
struct ore_striping_info {size_t cur_pg; size_t cur_comp; } ;
struct __stripe_pages_2d {int needed; int pages_in_unit; struct __1_page_stripe* _1p_stripes; } ;
struct __1_page_stripe {int /*<<< orphan*/  write_count; struct page** pages; } ;

/* Variables and functions */

void _ore_add_stripe_page(struct __stripe_pages_2d *sp2d,
		       struct ore_striping_info *si, struct page *page)
{
	struct __1_page_stripe *_1ps;

	sp2d->needed = true;

	_1ps = &sp2d->_1p_stripes[si->cur_pg];
	_1ps->pages[si->cur_comp] = page;
	++_1ps->write_count;

	si->cur_pg = (si->cur_pg + 1) % sp2d->pages_in_unit;
	/* si->cur_comp is advanced outside at main loop */
}