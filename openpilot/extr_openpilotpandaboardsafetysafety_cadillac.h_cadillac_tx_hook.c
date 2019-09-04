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
 int /*<<< orphan*/  CADILLAC_DRIVER_TORQUE_ALLOWANCE ; 
 int /*<<< orphan*/  CADILLAC_DRIVER_TORQUE_FACTOR ; 
 int /*<<< orphan*/  CADILLAC_MAX_RATE_DOWN ; 
 int /*<<< orphan*/  CADILLAC_MAX_RATE_UP ; 
 int /*<<< orphan*/  CADILLAC_MAX_RT_DELTA ; 
 int /*<<< orphan*/  CADILLAC_MAX_STEER ; 
 int CADILLAC_RT_INTERVAL ; 
 TYPE_3__* TIM2 ; 
 int* cadillac_desired_torque_last ; 
 int cadillac_get_torque_idx (int) ; 
 int cadillac_rt_torque_last ; 
 scalar_t__ cadillac_supercruise_on ; 
 int /*<<< orphan*/  cadillac_torque_driver ; 
 int cadillac_ts_last ; 
 scalar_t__ controls_allowed ; 
 int driver_limit_check (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_ts_elapsed (int,int) ; 
 int max_limit_check (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt_rate_limit_check (int,int,int /*<<< orphan*/ ) ; 
 int to_signed (int,int) ; 

__attribute__((used)) static int cadillac_tx_hook(CAN_FIFOMailBox_TypeDef *to_send) {
  uint32_t addr = to_send->RIR >> 21;

  // steer cmd checks
  if (addr == 0x151 || addr == 0x152 || addr == 0x153 || addr == 0x154) {
    int desired_torque = ((to_send->RDLR & 0x3f) << 8) + ((to_send->RDLR & 0xff00) >> 8);
    int violation = 0;
    uint32_t ts = TIM2->CNT;
    int idx = cadillac_get_torque_idx(addr);
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
      return false;
    }

  }
  return true;
}