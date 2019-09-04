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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASAN_PAGE_REDZONE ; 
 int /*<<< orphan*/  KASAN_SHADOW_SCALE_SIZE ; 
 unsigned long PAGE_SIZE ; 
 unsigned long compound_order (struct page*) ; 
 scalar_t__ gfpflags_allow_blocking (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasan_poison_shadow (void*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasan_unpoison_shadow (void const*,size_t) ; 
 int /*<<< orphan*/  quarantine_reduce () ; 
 unsigned long round_up (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct page* virt_to_page (void const*) ; 

void kasan_kmalloc_large(const void *ptr, size_t size, gfp_t flags)
{
	struct page *page;
	unsigned long redzone_start;
	unsigned long redzone_end;

	if (gfpflags_allow_blocking(flags))
		quarantine_reduce();

	if (unlikely(ptr == NULL))
		return;

	page = virt_to_page(ptr);
	redzone_start = round_up((unsigned long)(ptr + size),
				KASAN_SHADOW_SCALE_SIZE);
	redzone_end = (unsigned long)ptr + (PAGE_SIZE << compound_order(page));

	kasan_unpoison_shadow(ptr, size);
	kasan_poison_shadow((void *)redzone_start, redzone_end - redzone_start,
		KASAN_PAGE_REDZONE);
}