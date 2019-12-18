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
 scalar_t__ CRIU_GCOUNTER_SHM ; 
 scalar_t__ LSCRIU_Get_Global_Counter_Type () ; 
 int /*<<< orphan*/  s_initial_start_reqs ; 

__attribute__((used)) static int LSCRIU_Init_Global_Counter(int value)
{
    if (LSCRIU_Get_Global_Counter_Type() != CRIU_GCOUNTER_SHM
        || !s_initial_start_reqs) {
        return 0;
    }

    return 0;
}