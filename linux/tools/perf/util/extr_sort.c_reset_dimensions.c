#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ taken; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* bstack_sort_dimensions ; 
 TYPE_1__* common_sort_dimensions ; 
 TYPE_1__* hpp_sort_dimensions ; 
 TYPE_1__* memory_sort_dimensions ; 

void reset_dimensions(void)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(common_sort_dimensions); i++)
		common_sort_dimensions[i].taken = 0;

	for (i = 0; i < ARRAY_SIZE(hpp_sort_dimensions); i++)
		hpp_sort_dimensions[i].taken = 0;

	for (i = 0; i < ARRAY_SIZE(bstack_sort_dimensions); i++)
		bstack_sort_dimensions[i].taken = 0;

	for (i = 0; i < ARRAY_SIZE(memory_sort_dimensions); i++)
		memory_sort_dimensions[i].taken = 0;
}