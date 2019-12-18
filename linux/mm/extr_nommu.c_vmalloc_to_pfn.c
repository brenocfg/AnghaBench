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
 unsigned long page_to_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (void const*) ; 

unsigned long vmalloc_to_pfn(const void *addr)
{
	return page_to_pfn(virt_to_page(addr));
}