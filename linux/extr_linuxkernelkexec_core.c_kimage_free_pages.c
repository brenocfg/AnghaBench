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
 int /*<<< orphan*/  ClearPageReserved (struct page*) ; 
 int /*<<< orphan*/  __free_pages (struct page*,unsigned int) ; 
 int /*<<< orphan*/  arch_kexec_pre_free_pages (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 unsigned int page_private (struct page*) ; 

__attribute__((used)) static void kimage_free_pages(struct page *page)
{
	unsigned int order, count, i;

	order = page_private(page);
	count = 1 << order;

	arch_kexec_pre_free_pages(page_address(page), count);

	for (i = 0; i < count; i++)
		ClearPageReserved(page + i);
	__free_pages(page, order);
}