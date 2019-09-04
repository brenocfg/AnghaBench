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
 unsigned long RADIX_DAX_PMD ; 

__attribute__((used)) static int dax_is_pte_entry(void *entry)
{
	return !((unsigned long)entry & RADIX_DAX_PMD);
}