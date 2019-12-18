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
 unsigned long atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_vmalloc_pages ; 

unsigned long vmalloc_nr_pages(void)
{
	return atomic_long_read(&nr_vmalloc_pages);
}