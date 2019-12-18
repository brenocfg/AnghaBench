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
 int /*<<< orphan*/  PAGE_POISON ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  kasan_disable_current () ; 
 int /*<<< orphan*/  kasan_enable_current () ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void poison_page(struct page *page)
{
	void *addr = kmap_atomic(page);

	/* KASAN still think the page is in-use, so skip it. */
	kasan_disable_current();
	memset(addr, PAGE_POISON, PAGE_SIZE);
	kasan_enable_current();
	kunmap_atomic(addr);
}