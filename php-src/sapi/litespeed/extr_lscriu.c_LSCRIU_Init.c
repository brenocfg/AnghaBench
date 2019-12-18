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
 int /*<<< orphan*/  LSAPI_Register_Pgrp_Timer_Callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSCRIU_Debugging () ; 
 int /*<<< orphan*/  LSCRIU_Init_Env_Parameters () ; 
 int /*<<< orphan*/  LSCRIU_Init_Global_Counter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSCRIU_Wink_Server_is_Ready () ; 
 int LSCRIU_load_liblscapi () ; 
 int /*<<< orphan*/  LSCRIU_on_timer ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  lscriu_dbg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ s_initial_start_reqs ; 
 int /*<<< orphan*/  s_native ; 
 int /*<<< orphan*/  s_pid ; 

int LSCRIU_Init(void)
{
    s_pid = getpid();
    LSCRIU_Debugging();
    LSCRIU_Init_Env_Parameters();
    if (s_initial_start_reqs && !s_native) {
        if (LSCRIU_load_liblscapi() == -1)
            s_initial_start_reqs = 0;
    }
    if (s_initial_start_reqs) {
        LSCRIU_Wink_Server_is_Ready();
        lscriu_dbg("LSCRIU (%d): LSAPI_Register_Pgrp_Timer_Callback\n", s_pid);
        LSAPI_Register_Pgrp_Timer_Callback(LSCRIU_on_timer);
        LSCRIU_Init_Global_Counter(0);
    }
    return s_initial_start_reqs > 0;
}