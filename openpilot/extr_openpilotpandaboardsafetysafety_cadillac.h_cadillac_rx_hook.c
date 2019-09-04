#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int RDTR; int RIR; int RDLR; int RDHR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 int cadillac_cruise_engaged_last ; 
 int cadillac_ign ; 
 int cadillac_supercruise_on ; 
 int /*<<< orphan*/  cadillac_torque_driver ; 
 int controls_allowed ; 
 int to_signed (int,int) ; 
 int /*<<< orphan*/  update_sample (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void cadillac_rx_hook(CAN_FIFOMailBox_TypeDef *to_push) {
  int bus_number = (to_push->RDTR >> 4) & 0xFF;
  uint32_t addr = to_push->RIR >> 21;

  if (addr == 356) {
    int torque_driver_new = ((to_push->RDLR & 0x7) << 8) | ((to_push->RDLR >> 8) & 0xFF);
    torque_driver_new = to_signed(torque_driver_new, 11);
    // update array of samples
    update_sample(&cadillac_torque_driver, torque_driver_new);
  }

  // this message isn't all zeros when ignition is on
  if (addr == 0x160 && bus_number == 0) {
    cadillac_ign = to_push->RDLR > 0;
  }

  // enter controls on rising edge of ACC, exit controls on ACC off
  if ((addr == 0x370) && (bus_number == 0)) {
    int cruise_engaged = to_push->RDLR & 0x800000;  // bit 23
    if (cruise_engaged && !cadillac_cruise_engaged_last) {
      controls_allowed = 1;
    } else if (!cruise_engaged) {
      controls_allowed = 0;
    }
    cadillac_cruise_engaged_last = cruise_engaged;
  }

  // know supercruise mode and block openpilot msgs if on
  if ((addr == 0x152) || (addr == 0x154)) {
    cadillac_supercruise_on = (to_push->RDHR>>4) & 0x1;
  }
}