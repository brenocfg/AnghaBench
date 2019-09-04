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
 int GFP_KERNEL ; 
 int XT_MAX_TABLE_SIZE ; 
 int __GFP_ZERO ; 
 unsigned int* kvmalloc_array (unsigned int,int,int) ; 

unsigned int *xt_alloc_entry_offsets(unsigned int size)
{
	if (size > XT_MAX_TABLE_SIZE / sizeof(unsigned int))
		return NULL;

	return kvmalloc_array(size, sizeof(unsigned int), GFP_KERNEL | __GFP_ZERO);

}