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
 int /*<<< orphan*/  KASAN_KMALLOC_REDZONE ; 
 unsigned long compound_nr (struct page*) ; 
 int /*<<< orphan*/  kasan_poison_shadow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  page_kasan_tag_reset (struct page*) ; 
 int /*<<< orphan*/  page_size (struct page*) ; 

void kasan_poison_slab(struct page *page)
{
	unsigned long i;

	for (i = 0; i < compound_nr(page); i++)
		page_kasan_tag_reset(page + i);
	kasan_poison_shadow(page_address(page), page_size(page),
			KASAN_KMALLOC_REDZONE);
}