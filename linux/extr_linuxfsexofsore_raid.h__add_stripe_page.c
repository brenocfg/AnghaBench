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
struct ore_striping_info {int dummy; } ;
struct __stripe_pages_2d {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ore_add_stripe_page (struct __stripe_pages_2d*,struct ore_striping_info*,struct page*) ; 

__attribute__((used)) static inline void _add_stripe_page(struct __stripe_pages_2d *sp2d,
				struct ore_striping_info *si, struct page *page)
{
	if (!sp2d) /* Inline the fast path */
		return; /* Hay no raid stuff */
	_ore_add_stripe_page(sp2d, si, page);
}