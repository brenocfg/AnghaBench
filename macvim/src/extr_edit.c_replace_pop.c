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
 scalar_t__* replace_stack ; 
 size_t replace_stack_nr ; 

__attribute__((used)) static int
replace_pop()
{
    if (replace_stack_nr == 0)
	return -1;
    return (int)replace_stack[--replace_stack_nr];
}