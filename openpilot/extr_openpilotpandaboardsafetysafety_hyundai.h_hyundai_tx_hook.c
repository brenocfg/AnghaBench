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
 int /*<<< orphan*/  HYUNDAI_DRIVER_TORQUE_ALLOWANCE ; 
 int /*<<< orphan*/  HYUNDAI_DRIVER_TORQUE_FACTOR ; 
 int /*<<< orphan*/  HYUNDAI_MAX_RATE_DOWN ; 
 int /*<<< orphan*/  HYUNDAI_MAX_RATE_UP ; 
 int /*<<< orphan*/  HYUNDAI_MAX_RT_DELTA ; 
 int /*<<< orphan*/  HYUNDAI_MAX_STEER ; 
 int HYUNDAI_RT_INTERVAL ; 
 TYPE_3__* TIM2 ; 
 scalar_t__ controls_allowed ; 
 int driver_limit_check (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_ts_elapsed (int,int) ; 
 scalar_t__ hyundai_camera_detected ; 
 int hyundai_desired_torque_last ; 
 int hyundai_rt_torque_last ; 
 int /*<<< orphan*/  hyundai_torque_driver ; 
 int hyundai_ts_last ; 
 int max_limit_check (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt_rate_limit_check (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hyundai_tx_hook(CAN_FIFOMailBox_TypeDef *to_send) {

  // There can be only one! (camera)
  if (hyundai_camera_detected) {
    return 0;
  }

  uint32_t addr;
  if (to_send->RIR & 4) {
    // Extended
    addr = to_send->RIR >> 3;
  } else {
    // Normal
    addr = to_send->RIR >> 21;
  }

  // LKA STEER: safety check
  if (addr == 832) {
    int desired_torque = ((to_send->RDLR >> 16) & 0x7ff) - 1024;
    uint32_t ts = TIM2->CNT;
    int violation = 0;

    if (controls_allowed) {

      // *** global torque limit check ***
      violation |= max_limit_check(desired_torque, HYUNDAI_MAX_STEER, -HYUNDAI_MAX_STEER);

      // *** torque rate limit check ***
      violation |= driver_limit_check(desired_torque, hyundai_desired_torque_last, &hyundai_torque_driver,
        HYUNDAI_MAX_STEER, HYUNDAI_MAX_RATE_UP, HYUNDAI_MAX_RATE_DOWN,
        HYUNDAI_DRIVER_TORQUE_ALLOWANCE, HYUNDAI_DRIVER_TORQUE_FACTOR);

      // used next time
      hyundai_desired_torque_last = desired_torque;

      // *** torque real time rate limit check ***
      violation |= rt_rate_limit_check(desired_torque, hyundai_rt_torque_last, HYUNDAI_MAX_RT_DELTA);

      // every RT_INTERVAL set the new limits
      uint32_t ts_elapsed = get_ts_elapsed(ts, hyundai_ts_last);
      if (ts_elapsed > HYUNDAI_RT_INTERVAL) {
        hyundai_rt_torque_last = desired_torque;
        hyundai_ts_last = ts;
      }
    }

    // no torque if controls is not allowed
    if (!controls_allowed && (desired_torque != 0)) {
      violation = 1;
    }

    // reset to 0 if either controls is not allowed or there's a violation
    if (violation || !controls_allowed) {
      hyundai_desired_torque_last = 0;
      hyundai_rt_torque_last = 0;
      hyundai_ts_last = ts;
    }

    if (violation) {
      return false;
    }
  }

  // FORCE CANCEL: safety check only relevant when spamming the cancel button.
  // ensuring that only the cancel button press is sent (VAL 4) when controls are off.
  // This avoids unintended engagements while still allowing resume spam
  // TODO: fix bug preventing the button msg to be fwd'd on bus 2
  //if (((to_send->RIR>>21) == 1265) && !controls_allowed && ((to_send->RDTR >> 4) & 0xFF) == 0) {
  //  if ((to_send->RDLR & 0x7) != 4) return 0;
  //}

  // 1 allows the message through
  return true;
}