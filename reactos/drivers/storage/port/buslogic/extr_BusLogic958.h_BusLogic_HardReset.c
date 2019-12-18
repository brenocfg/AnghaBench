#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  HardReset; } ;
struct TYPE_7__ {scalar_t__ All; TYPE_1__ Bits; } ;
struct TYPE_6__ {scalar_t__ IO_Address; } ;
typedef  TYPE_2__ BusLogic_HostAdapter_T ;
typedef  TYPE_3__ BusLogic_ControlRegister_T ;

/* Variables and functions */
 scalar_t__ BusLogic_ControlRegisterOffset ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WriteBusLogicPort (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
BusLogic_HardReset(BusLogic_HostAdapter_T *HostAdapter)
{
  BusLogic_ControlRegister_T ControlRegister;
  ControlRegister.All = 0;
  ControlRegister.Bits.HardReset = TRUE;
  WriteBusLogicPort(ControlRegister.All,
       HostAdapter->IO_Address + BusLogic_ControlRegisterOffset);
}