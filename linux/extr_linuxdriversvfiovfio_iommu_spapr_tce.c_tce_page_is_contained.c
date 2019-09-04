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

/* Variables and functions */
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  compound_head (struct page*) ; 
 unsigned int compound_order (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tce_page_is_contained(struct page *page, unsigned page_shift)
{
	/*
	 * Check that the TCE table granularity is not bigger than the size of
	 * a page we just found. Otherwise the hardware can get access to
	 * a bigger memory chunk that it should.
	 */
	return (PAGE_SHIFT + compound_order(compound_head(page))) >= page_shift;
}