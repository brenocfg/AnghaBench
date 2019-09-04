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
 int /*<<< orphan*/  SUBARU_DRIVER_TORQUE_ALLOWANCE ; 
 int /*<<< orphan*/  SUBARU_DRIVER_TORQUE_FACTOR ; 
 int /*<<< orphan*/  SUBARU_MAX_RATE_DOWN ; 
 int /*<<< orphan*/  SUBARU_MAX_RATE_UP ; 
 int /*<<< orphan*/  SUBARU_MAX_RT_DELTA ; 
 int /*<<< orphan*/  SUBARU_MAX_STEER ; 
 int SUBARU_RT_INTERVAL ; 
 TYPE_3__* TIM2 ; 
 scalar_t__ controls_allowed ; 
 int driver_limit_check (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_ts_elapsed (int,int) ; 
 int max_limit_check (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt_rate_limit_check (int,int,int /*<<< orphan*/ ) ; 
 int subaru_desired_torque_last ; 
 int subaru_rt_torque_last ; 
 int /*<<< orphan*/  subaru_torque_driver ; 
 int subaru_ts_last ; 
 int to_signed (int,int) ; 

__attribute__((used)) static int subaru_tx_hook(CAN_FIFOMailBox_TypeDef *to_send) {
  uint32_t addr = to_send->RIR >> 21;

  // steer cmd checks
  if (addr == 0x122) {
    int desired_torque = ((to_send->RDLR >> 16) & 0x1FFF);
    int violation = 0;
    uint32_t ts = TIM2->CNT;
    desired_torque = to_signed(desired_torque, 13);

    if (controls_allowed) {

      // *** global torque limit check ***
      violation |= max_limit_check(desired_torque, SUBARU_MAX_STEER, -SUBARU_MAX_STEER);

      // *** torque rate limit check ***
      int desired_torque_last = subaru_desired_torque_last;
      violation |= driver_limit_check(desired_torque, desired_torque_last, &subaru_torque_driver,
        SUBARU_MAX_STEER, SUBARU_MAX_RATE_UP, SUBARU_MAX_RATE_DOWN,
        SUBARU_DRIVER_TORQUE_ALLOWANCE, SUBARU_DRIVER_TORQUE_FACTOR);

      // used next time
      subaru_desired_torque_last = desired_torque;

      // *** torque real time rate limit check ***
      violation |= rt_rate_limit_check(desired_torque, subaru_rt_torque_last, SUBARU_MAX_RT_DELTA);

      // every RT_INTERVAL set the new limits
      uint32_t ts_elapsed = get_ts_elapsed(ts, subaru_ts_last);
      if (ts_elapsed > SUBARU_RT_INTERVAL) {
        subaru_rt_torque_last = desired_torque;
        subaru_ts_last = ts;
      }
    }

    // no torque if controls is not allowed
    if (!controls_allowed && (desired_torque != 0)) {
      violation = 1;
    }

    // reset to 0 if either controls is not allowed or there's a violation
    if (violation || !controls_allowed) {
      subaru_desired_torque_last = 0;
      subaru_rt_torque_last = 0;
      subaru_ts_last = ts;
    }

    if (violation) {
      return false;
    }

  }
  return true;
}