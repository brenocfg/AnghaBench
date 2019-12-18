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
typedef  int /*<<< orphan*/  u8 ;
struct page {int dummy; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 int /*<<< orphan*/  kasan_unpoison_shadow (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  page_kasan_tag_set (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  random_tag () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void kasan_alloc_pages(struct page *page, unsigned int order)
{
	u8 tag;
	unsigned long i;

	if (unlikely(PageHighMem(page)))
		return;

	tag = random_tag();
	for (i = 0; i < (1 << order); i++)
		page_kasan_tag_set(page + i, tag);
	kasan_unpoison_shadow(page_address(page), PAGE_SIZE << order);
}