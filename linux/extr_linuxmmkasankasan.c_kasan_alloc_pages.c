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
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 int /*<<< orphan*/  kasan_unpoison_shadow (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 

void kasan_alloc_pages(struct page *page, unsigned int order)
{
	if (likely(!PageHighMem(page)))
		kasan_unpoison_shadow(page_address(page), PAGE_SIZE << order);
}