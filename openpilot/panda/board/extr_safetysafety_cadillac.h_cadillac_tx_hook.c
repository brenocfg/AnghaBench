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
 int /*<<< orphan*/  CADILLAC_DRIVER_TORQUE_ALLOWANCE ; 
 int /*<<< orphan*/  CADILLAC_DRIVER_TORQUE_FACTOR ; 
 int /*<<< orphan*/  CADILLAC_MAX_RATE_DOWN ; 
 int /*<<< orphan*/  CADILLAC_MAX_RATE_UP ; 
 int /*<<< orphan*/  CADILLAC_MAX_RT_DELTA ; 
 int /*<<< orphan*/  CADILLAC_MAX_STEER ; 
 scalar_t__ CADILLAC_RT_INTERVAL ; 
 int /*<<< orphan*/  CADILLAC_TORQUE_MSG_N ; 
 int GET_ADDR (int /*<<< orphan*/ *) ; 
 int GET_BYTE (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* TIM2 ; 
 int* cadillac_desired_torque_last ; 
 int cadillac_get_torque_idx (int,int /*<<< orphan*/ ) ; 
 int cadillac_rt_torque_last ; 
 scalar_t__ cadillac_supercruise_on ; 
 int /*<<< orphan*/  cadillac_torque_driver ; 
 scalar_t__ cadillac_ts_last ; 
 scalar_t__ controls_allowed ; 
 int driver_limit_check (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_ts_elapsed (scalar_t__,scalar_t__) ; 
 int max_limit_check (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt_rate_limit_check (int,int,int /*<<< orphan*/ ) ; 
 int to_signed (int,int) ; 

__attribute__((used)) static int cadillac_tx_hook(CAN_FIFOMailBox_TypeDef *to_send) {
  int tx = 1;
  int addr = GET_ADDR(to_send);

  // steer cmd checks
  if ((addr == 0x151) || (addr == 0x152) || (addr == 0x153) || (addr == 0x154)) {
    int desired_torque = ((GET_BYTE(to_send, 0) & 0x3f) << 8) | GET_BYTE(to_send, 1);
    int violation = 0;
    uint32_t ts = TIM2->CNT;
    int idx = cadillac_get_torque_idx(addr, CADILLAC_TORQUE_MSG_N);
    desired_torque = to_signed(desired_torque, 14);

    if (controls_allowed) {

      // *** global torque limit check ***
      violation |= max_limit_check(desired_torque, CADILLAC_MAX_STEER, -CADILLAC_MAX_STEER);

      // *** torque rate limit check ***
      int desired_torque_last = cadillac_desired_torque_last[idx];
      violation |= driver_limit_check(desired_torque, desired_torque_last, &cadillac_torque_driver,
        CADILLAC_MAX_STEER, CADILLAC_MAX_RATE_UP, CADILLAC_MAX_RATE_DOWN,
        CADILLAC_DRIVER_TORQUE_ALLOWANCE, CADILLAC_DRIVER_TORQUE_FACTOR);

      // used next time
      cadillac_desired_torque_last[idx] = desired_torque;

      // *** torque real time rate limit check ***
      violation |= rt_rate_limit_check(desired_torque, cadillac_rt_torque_last, CADILLAC_MAX_RT_DELTA);

      // every RT_INTERVAL set the new limits
      uint32_t ts_elapsed = get_ts_elapsed(ts, cadillac_ts_last);
      if (ts_elapsed > CADILLAC_RT_INTERVAL) {
        cadillac_rt_torque_last = desired_torque;
        cadillac_ts_last = ts;
      }
    }

    // no torque if controls is not allowed
    if (!controls_allowed && (desired_torque != 0)) {
      violation = 1;
    }

    // reset to 0 if either controls is not allowed or there's a violation
    if (violation || !controls_allowed) {
      cadillac_desired_torque_last[idx] = 0;
      cadillac_rt_torque_last = 0;
      cadillac_ts_last = ts;
    }

    if (violation || cadillac_supercruise_on) {
      tx = 0;
    }

  }
  return tx;
}