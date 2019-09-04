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
 int /*<<< orphan*/  CHRYSLER_MAX_RATE_DOWN ; 
 int /*<<< orphan*/  CHRYSLER_MAX_RATE_UP ; 
 int /*<<< orphan*/  CHRYSLER_MAX_RT_DELTA ; 
 int /*<<< orphan*/  CHRYSLER_MAX_STEER ; 
 int /*<<< orphan*/  CHRYSLER_MAX_TORQUE_ERROR ; 
 int CHRYSLER_RT_INTERVAL ; 
 TYPE_3__* TIM2 ; 
 scalar_t__ chrysler_camera_detected ; 
 int chrysler_desired_torque_last ; 
 int chrysler_rt_torque_last ; 
 int /*<<< orphan*/  chrysler_torque_meas ; 
 int chrysler_ts_last ; 
 scalar_t__ controls_allowed ; 
 int dist_to_meas_check (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_ts_elapsed (int,int) ; 
 int max_limit_check (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt_rate_limit_check (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chrysler_tx_hook(CAN_FIFOMailBox_TypeDef *to_send) {

  // There can be only one! (camera)
  if (chrysler_camera_detected) {
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


  // LKA STEER
  if (addr == 0x292) {
    int rdlr = to_send->RDLR;
    int desired_torque = ((rdlr & 0x7) << 8) + ((rdlr & 0xFF00) >> 8) - 1024;
    uint32_t ts = TIM2->CNT;
    int violation = 0;

    if (controls_allowed) {

      // *** global torque limit check ***
      violation |= max_limit_check(desired_torque, CHRYSLER_MAX_STEER, -CHRYSLER_MAX_STEER);

      // *** torque rate limit check ***
      violation |= dist_to_meas_check(desired_torque, chrysler_desired_torque_last,
        &chrysler_torque_meas, CHRYSLER_MAX_RATE_UP, CHRYSLER_MAX_RATE_DOWN, CHRYSLER_MAX_TORQUE_ERROR);

      // used next time
      chrysler_desired_torque_last = desired_torque;

      // *** torque real time rate limit check ***
      violation |= rt_rate_limit_check(desired_torque, chrysler_rt_torque_last, CHRYSLER_MAX_RT_DELTA);

      // every RT_INTERVAL set the new limits
      uint32_t ts_elapsed = get_ts_elapsed(ts, chrysler_ts_last);
      if (ts_elapsed > CHRYSLER_RT_INTERVAL) {
        chrysler_rt_torque_last = desired_torque;
        chrysler_ts_last = ts;
      }
    }

    // no torque if controls is not allowed
    if (!controls_allowed && (desired_torque != 0)) {
      violation = 1;
    }

    // reset to 0 if either controls is not allowed or there's a violation
    if (violation || !controls_allowed) {
      chrysler_desired_torque_last = 0;
      chrysler_rt_torque_last = 0;
      chrysler_ts_last = ts;
    }

    if (violation) {
      return false;
    }
  }

  // FORCE CANCEL: safety check only relevant when spamming the cancel button.
  // ensuring that only the cancel button press is sent when controls are off.
  // This avoids unintended engagements while still allowing resume spam
  // TODO: fix bug preventing the button msg to be fwd'd on bus 2

  // 1 allows the message through
  return true;
}