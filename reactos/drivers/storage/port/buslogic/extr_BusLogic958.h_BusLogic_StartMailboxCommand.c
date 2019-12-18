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
typedef  int /*<<< orphan*/  BusLogic_HostAdapter_T ;

/* Variables and functions */
 int /*<<< orphan*/  BusLogic_ExecuteMailboxCommand ; 
 int /*<<< orphan*/  BusLogic_WriteCommandParameterRegister (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
BusLogic_StartMailboxCommand(BusLogic_HostAdapter_T *HostAdapter)
{
  BusLogic_WriteCommandParameterRegister(HostAdapter,
                                         BusLogic_ExecuteMailboxCommand);
}