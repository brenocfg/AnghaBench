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
typedef  int /*<<< orphan*/  CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 int GET_ADDR (int /*<<< orphan*/ *) ; 
 int GET_BUS (int /*<<< orphan*/ *) ; 
 int GET_BYTE (int /*<<< orphan*/ *,int) ; 
 int cadillac_cruise_engaged_last ; 
 int cadillac_supercruise_on ; 
 int /*<<< orphan*/  cadillac_torque_driver ; 
 int controls_allowed ; 
 int to_signed (int,int) ; 
 int /*<<< orphan*/  update_sample (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void cadillac_rx_hook(CAN_FIFOMailBox_TypeDef *to_push) {
  int bus = GET_BUS(to_push);
  int addr = GET_ADDR(to_push);

  if (addr == 356) {
    int torque_driver_new = ((GET_BYTE(to_push, 0) & 0x7U) << 8) | (GET_BYTE(to_push, 1));

    torque_driver_new = to_signed(torque_driver_new, 11);
    // update array of samples
    update_sample(&cadillac_torque_driver, torque_driver_new);
  }

  // enter controls on rising edge of ACC, exit controls on ACC off
  if ((addr == 0x370) && (bus == 0)) {
    int cruise_engaged = GET_BYTE(to_push, 2) & 0x80;  // bit 23
    if (cruise_engaged && !cadillac_cruise_engaged_last) {
      controls_allowed = 1;
    }
    if (!cruise_engaged) {
      controls_allowed = 0;
    }
    cadillac_cruise_engaged_last = cruise_engaged;
  }

  // know supercruise mode and block openpilot msgs if on
  if ((addr == 0x152) || (addr == 0x154)) {
    cadillac_supercruise_on = (GET_BYTE(to_push, 4) & 0x10) != 0;
  }
}