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
typedef  int /*<<< orphan*/  LSAPI_On_Timer_pf ;

/* Variables and functions */
 int /*<<< orphan*/  s_proc_group_timer_cb ; 

void LSAPI_Register_Pgrp_Timer_Callback(LSAPI_On_Timer_pf cb)
{
    s_proc_group_timer_cb = cb;
}