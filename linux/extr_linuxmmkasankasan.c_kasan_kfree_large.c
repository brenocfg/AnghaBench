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

/* Variables and functions */
 int /*<<< orphan*/  kasan_report_invalid_free (void*,unsigned long) ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_head_page (void*) ; 

void kasan_kfree_large(void *ptr, unsigned long ip)
{
	if (ptr != page_address(virt_to_head_page(ptr)))
		kasan_report_invalid_free(ptr, ip);
	/* The object will be poisoned by page_alloc. */
}