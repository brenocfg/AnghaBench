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
 int controls_allowed ; 
 int gm_ascm_detected ; 
 int gm_brake_prev ; 
 int gm_gas_prev ; 
 int gm_moving ; 
 int /*<<< orphan*/  gm_torque_driver ; 
 scalar_t__ long_controls_allowed ; 
 int to_signed (int,int) ; 
 int /*<<< orphan*/  update_sample (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void gm_rx_hook(CAN_FIFOMailBox_TypeDef *to_push) {
  int bus_number = GET_BUS(to_push);
  int addr = GET_ADDR(to_push);

  if (addr == 388) {
    int torque_driver_new = ((GET_BYTE(to_push, 6) & 0x7) << 8) | GET_BYTE(to_push, 7);
    torque_driver_new = to_signed(torque_driver_new, 11);
    // update array of samples
    update_sample(&gm_torque_driver, torque_driver_new);
  }

  // sample speed, really only care if car is moving or not
  // rear left wheel speed
  if (addr == 842) {
    gm_moving = GET_BYTE(to_push, 0) | GET_BYTE(to_push, 1);
  }

  // Check if ASCM or LKA camera are online
  // on powertrain bus.
  // 384 = ASCMLKASteeringCmd
  // 715 = ASCMGasRegenCmd
  if ((bus_number == 0) && ((addr == 384) || (addr == 715))) {
    gm_ascm_detected = 1;
    controls_allowed = 0;
  }

  // ACC steering wheel buttons
  if (addr == 481) {
    int button = (GET_BYTE(to_push, 5) & 0x70) >> 4;
    switch (button) {
      case 2:  // resume
      case 3:  // set
        controls_allowed = 1;
        break;
      case 6:  // cancel
        controls_allowed = 0;
        break;
      default:
        break;  // any other button is irrelevant
    }
  }

  // exit controls on rising edge of brake press or on brake press when
  // speed > 0
  if (addr == 241) {
    int brake = GET_BYTE(to_push, 1);
    // Brake pedal's potentiometer returns near-zero reading
    // even when pedal is not pressed
    if (brake < 10) {
      brake = 0;
    }
    if (brake && (!gm_brake_prev || gm_moving)) {
       controls_allowed = 0;
    }
    gm_brake_prev = brake;
  }

  // exit controls on rising edge of gas press
  if (addr == 417) {
    int gas = GET_BYTE(to_push, 6);
    if (gas && !gm_gas_prev && long_controls_allowed) {
      controls_allowed = 0;
    }
    gm_gas_prev = gas;
  }

  // exit controls on regen paddle
  if (addr == 189) {
    bool regen = GET_BYTE(to_push, 0) & 0x20;
    if (regen) {
      controls_allowed = 0;
    }
  }
}