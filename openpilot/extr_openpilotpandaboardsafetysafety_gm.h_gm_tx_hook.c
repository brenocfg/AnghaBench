#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int CNT; } ;
struct TYPE_4__ {int RIR; int RDLR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  GM_DRIVER_TORQUE_ALLOWANCE ; 
 int /*<<< orphan*/  GM_DRIVER_TORQUE_FACTOR ; 
 int GM_MAX_BRAKE ; 
 int GM_MAX_GAS ; 
 int /*<<< orphan*/  GM_MAX_RATE_DOWN ; 
 int /*<<< orphan*/  GM_MAX_RATE_UP ; 
 int GM_MAX_REGEN ; 
 int /*<<< orphan*/  GM_MAX_RT_DELTA ; 
 int /*<<< orphan*/  GM_MAX_STEER ; 
 int GM_RT_INTERVAL ; 
 TYPE_3__* TIM2 ; 
 scalar_t__ controls_allowed ; 
 int driver_limit_check (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_ts_elapsed (int,int) ; 
 scalar_t__ gm_ascm_detected ; 
 scalar_t__ gm_brake_prev ; 
 int gm_desired_torque_last ; 
 scalar_t__ gm_gas_prev ; 
 int gm_rt_torque_last ; 
 scalar_t__ gm_speed ; 
 int /*<<< orphan*/  gm_torque_driver ; 
 int gm_ts_last ; 
 int max_limit_check (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt_rate_limit_check (int,int,int /*<<< orphan*/ ) ; 
 int to_signed (int,int) ; 

__attribute__((used)) static int gm_tx_hook(CAN_FIFOMailBox_TypeDef *to_send) {

  // There can be only one! (ASCM)
  if (gm_ascm_detected) {
    return 0;
  }

  // disallow actuator commands if gas or brake (with vehicle moving) are pressed
  // and the the latching controls_allowed flag is True
  int pedal_pressed = gm_gas_prev || (gm_brake_prev && gm_speed);
  int current_controls_allowed = controls_allowed && !pedal_pressed;

  uint32_t addr;
  if (to_send->RIR & 4) {
    // Extended
    addr = to_send->RIR >> 3;
  } else {
    // Normal
    addr = to_send->RIR >> 21;
  }

  // BRAKE: safety check
  if (addr == 789) {
    int rdlr = to_send->RDLR;
    int brake = ((rdlr & 0xF) << 8) + ((rdlr & 0xFF00) >> 8);
    brake = (0x1000 - brake) & 0xFFF;
    if (current_controls_allowed) {
      if (brake > GM_MAX_BRAKE) return 0;
    } else {
      if (brake != 0) return 0;
    }
  }

  // LKA STEER: safety check
  if (addr == 384) {
    int rdlr = to_send->RDLR;
    int desired_torque = ((rdlr & 0x7) << 8) + ((rdlr & 0xFF00) >> 8);
    uint32_t ts = TIM2->CNT;
    int violation = 0;
    desired_torque = to_signed(desired_torque, 11);

    if (current_controls_allowed) {

      // *** global torque limit check ***
      violation |= max_limit_check(desired_torque, GM_MAX_STEER, -GM_MAX_STEER);

      // *** torque rate limit check ***
      violation |= driver_limit_check(desired_torque, gm_desired_torque_last, &gm_torque_driver,
        GM_MAX_STEER, GM_MAX_RATE_UP, GM_MAX_RATE_DOWN,
        GM_DRIVER_TORQUE_ALLOWANCE, GM_DRIVER_TORQUE_FACTOR);

      // used next time
      gm_desired_torque_last = desired_torque;

      // *** torque real time rate limit check ***
      violation |= rt_rate_limit_check(desired_torque, gm_rt_torque_last, GM_MAX_RT_DELTA);

      // every RT_INTERVAL set the new limits
      uint32_t ts_elapsed = get_ts_elapsed(ts, gm_ts_last);
      if (ts_elapsed > GM_RT_INTERVAL) {
        gm_rt_torque_last = desired_torque;
        gm_ts_last = ts;
      }
    }

    // no torque if controls is not allowed
    if (!current_controls_allowed && (desired_torque != 0)) {
      violation = 1;
    }

    // reset to 0 if either controls is not allowed or there's a violation
    if (violation || !current_controls_allowed) {
      gm_desired_torque_last = 0;
      gm_rt_torque_last = 0;
      gm_ts_last = ts;
    }

    if (violation) {
      return false;
    }
  }

  // PARK ASSIST STEER: unlimited torque, no thanks
  if (addr == 823) return 0;

  // GAS/REGEN: safety check
  if (addr == 715) {
    int rdlr = to_send->RDLR;
    int gas_regen = ((rdlr & 0x7F0000) >> 11) + ((rdlr & 0xF8000000) >> 27);
    int apply = rdlr & 1;
    if (current_controls_allowed) {
      if (gas_regen > GM_MAX_GAS) return 0;
    } else {
      // Disabled message is !engaed with gas
      // value that corresponds to max regen.
      if (apply || gas_regen != GM_MAX_REGEN) return 0;
    }
  }

  // 1 allows the message through
  return true;
}