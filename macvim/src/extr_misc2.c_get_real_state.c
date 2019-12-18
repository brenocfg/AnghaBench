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
 int NORMAL ; 
 int OP_PENDING ; 
 int SELECTMODE ; 
 int State ; 
 int VISUAL ; 
 scalar_t__ VIsual_active ; 
 scalar_t__ VIsual_select ; 
 scalar_t__ finish_op ; 

int
get_real_state()
{
    if (State & NORMAL)
    {
	if (VIsual_active)
	{
	    if (VIsual_select)
		return SELECTMODE;
	    return VISUAL;
	}
	else if (finish_op)
	    return OP_PENDING;
    }
    return State;
}