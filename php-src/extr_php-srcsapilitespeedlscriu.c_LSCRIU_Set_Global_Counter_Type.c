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
typedef  scalar_t__ GlobalCounterType_t ;

/* Variables and functions */
 scalar_t__ CRIU_GCOUNTER_PIPE ; 
 scalar_t__ CRIU_GCOUNTER_SHM ; 
 scalar_t__ CRIU_GCOUNTER_SIG ; 
 scalar_t__ s_global_counter_type ; 

__attribute__((used)) static void LSCRIU_Set_Global_Counter_Type(GlobalCounterType_t tp)
{
    if ((tp == CRIU_GCOUNTER_SHM) || (tp == CRIU_GCOUNTER_SIG)
        || (tp == CRIU_GCOUNTER_PIPE)) {
        s_global_counter_type = tp;
    } else {
        s_global_counter_type = CRIU_GCOUNTER_SHM;
    }

}