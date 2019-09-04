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
struct TYPE_3__ {int RDTR; int RIR; int RDHR; int RDLR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 int controls_allowed ; 
 int gm_ascm_detected ; 
 int gm_brake_prev ; 
 int gm_gas_prev ; 
 int gm_ignition_started ; 
 int gm_speed ; 
 int /*<<< orphan*/  gm_torque_driver ; 
 int to_signed (int,int) ; 
 int /*<<< orphan*/  update_sample (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void gm_rx_hook(CAN_FIFOMailBox_TypeDef *to_push) {
  int bus_number = (to_push->RDTR >> 4) & 0xFF;
  uint32_t addr;
  if (to_push->RIR & 4) {
    // Extended
    // Not looked at, but have to be separated
    // to avoid address collision
    addr = to_push->RIR >> 3;
  } else {
    // Normal
    addr = to_push->RIR >> 21;
  }

  if (addr == 388) {
    int torque_driver_new = (((to_push->RDHR >> 16) & 0x7) << 8) | ((to_push->RDHR >> 24) & 0xFF);
    torque_driver_new = to_signed(torque_driver_new, 11);
    // update array of samples
    update_sample(&gm_torque_driver, torque_driver_new);
  }

  if (addr == 0x1f1 && bus_number == 0) {
    //Bit 5 should be ignition "on"
    //Backup plan is Bit 2 (accessory power)
    uint32_t ign = (to_push->RDLR) & 0x20;
    gm_ignition_started = ign > 0;
  }

  // sample speed, really only care if car is moving or not
  // rear left wheel speed
  if (addr == 842) {
    gm_speed = to_push->RDLR & 0xFFFF;
  }

  // Check if ASCM or LKA camera are online
  // on powertrain bus.
  // 384 = ASCMLKASteeringCmd
  // 715 = ASCMGasRegenCmd
  if (bus_number == 0 && (addr == 384 || addr == 715)) {
    gm_ascm_detected = 1;
    controls_allowed = 0;
  }

  // ACC steering wheel buttons
  if (addr == 481) {
    int buttons = (to_push->RDHR >> 12) & 0x7;
    // res/set - enable, cancel button - disable
    if (buttons == 2 || buttons == 3) {
      controls_allowed = 1;
    } else if (buttons == 6) {
      controls_allowed = 0;
    }
  }

  // exit controls on rising edge of brake press or on brake press when
  // speed > 0
  if (addr == 241) {
    int brake = (to_push->RDLR & 0xFF00) >> 8;
    // Brake pedal's potentiometer returns near-zero reading
    // even when pedal is not pressed
    if (brake < 10) {
      brake = 0;
    }
    if (brake && (!gm_brake_prev || gm_speed)) {
       controls_allowed = 0;
    }
    gm_brake_prev = brake;
  }

  // exit controls on rising edge of gas press
  if (addr == 417) {
    int gas = to_push->RDHR & 0xFF0000;
    if (gas && !gm_gas_prev) {
      controls_allowed = 0;
    }
    gm_gas_prev = gas;
  }

  // exit controls on regen paddle
  if (addr == 189) {
    int regen = to_push->RDLR & 0x20;
    if (regen) {
      controls_allowed = 0;
    }
  }
}