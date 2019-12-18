#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ CNT; } ;
typedef  int /*<<< orphan*/  CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  CHRYSLER_MAX_RATE_DOWN ; 
 int /*<<< orphan*/  CHRYSLER_MAX_RATE_UP ; 
 int /*<<< orphan*/  CHRYSLER_MAX_RT_DELTA ; 
 int /*<<< orphan*/  CHRYSLER_MAX_STEER ; 
 int /*<<< orphan*/  CHRYSLER_MAX_TORQUE_ERROR ; 
 scalar_t__ CHRYSLER_RT_INTERVAL ; 
 int GET_ADDR (int /*<<< orphan*/ *) ; 
 int GET_BYTE (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* TIM2 ; 
 scalar_t__ chrysler_camera_detected ; 
 int chrysler_desired_torque_last ; 
 int chrysler_rt_torque_last ; 
 int /*<<< orphan*/  chrysler_torque_meas ; 
 scalar_t__ chrysler_ts_last ; 
 scalar_t__ controls_allowed ; 
 int dist_to_meas_check (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_ts_elapsed (scalar_t__,scalar_t__) ; 
 int max_limit_check (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt_rate_limit_check (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chrysler_tx_hook(CAN_FIFOMailBox_TypeDef *to_send) {

  int tx = 1;

  // If camera is on bus 0, then nothing can be sent
  if (chrysler_camera_detected) {
    tx = 0;
  }

  int addr = GET_ADDR(to_send);

  // LKA STEER
  if (addr == 0x292) {
    int desired_torque = ((GET_BYTE(to_send, 0) & 0x7U) << 8) + GET_BYTE(to_send, 1) - 1024U;
    uint32_t ts = TIM2->CNT;
    bool violation = 0;

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
      tx = 0;
    }
  }

  // FORCE CANCEL: safety check only relevant when spamming the cancel button.
  // ensuring that only the cancel button press is sent when controls are off.
  // This avoids unintended engagements while still allowing resume spam
  // TODO: fix bug preventing the button msg to be fwd'd on bus 2

  // 1 allows the message through
  return tx;
}