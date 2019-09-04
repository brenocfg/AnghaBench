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
struct __stripe_pages_2d {int pages_in_unit; struct __1_page_stripe* _1p_stripes; } ;
struct __1_page_stripe {scalar_t__ write_count; } ;

/* Variables and functions */

__attribute__((used)) static unsigned _sp2d_max_pg(struct __stripe_pages_2d *sp2d)
{
	int p;

	for (p = sp2d->pages_in_unit - 1; p >= 0; --p) {
		struct __1_page_stripe *_1ps = &sp2d->_1p_stripes[p];

		if (_1ps->write_count)
			return p;
	}

	return ~0;
}