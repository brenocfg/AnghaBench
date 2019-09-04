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
typedef  int kimage_entry_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 struct page* boot_pfn_to_page (int) ; 
 int /*<<< orphan*/  kimage_free_pages (struct page*) ; 

__attribute__((used)) static void kimage_free_entry(kimage_entry_t entry)
{
	struct page *page;

	page = boot_pfn_to_page(entry >> PAGE_SHIFT);
	kimage_free_pages(page);
}