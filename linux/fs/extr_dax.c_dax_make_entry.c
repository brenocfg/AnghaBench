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
typedef  int /*<<< orphan*/  pfn_t ;

/* Variables and functions */
 unsigned long DAX_SHIFT ; 
 unsigned long pfn_t_to_pfn (int /*<<< orphan*/ ) ; 
 void* xa_mk_value (unsigned long) ; 

__attribute__((used)) static void *dax_make_entry(pfn_t pfn, unsigned long flags)
{
	return xa_mk_value(flags | (pfn_t_to_pfn(pfn) << DAX_SHIFT));
}