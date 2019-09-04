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
 scalar_t__ Ctrl_V ; 
 int INSERT ; 
 scalar_t__ MAYBE ; 
 int State ; 
 int VE_ALL ; 
 int VE_BLOCK ; 
 int VE_INSERT ; 
 scalar_t__ VIsual_active ; 
 scalar_t__ VIsual_mode ; 
 int ve_flags ; 
 scalar_t__ virtual_op ; 

int
virtual_active()
{
    /* While an operator is being executed we return "virtual_op", because
     * VIsual_active has already been reset, thus we can't check for "block"
     * being used. */
    if (virtual_op != MAYBE)
	return virtual_op;
    return (ve_flags == VE_ALL
	    || ((ve_flags & VE_BLOCK) && VIsual_active && VIsual_mode == Ctrl_V)
	    || ((ve_flags & VE_INSERT) && (State & INSERT)));
}