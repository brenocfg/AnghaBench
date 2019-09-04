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
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ CNT; } ;
struct TYPE_4__ {int RDTR; int RIR; int RDLR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 TYPE_3__* TIM2 ; 
 int /*<<< orphan*/  TOYOTA_MAX_ACCEL ; 
 int /*<<< orphan*/  TOYOTA_MAX_RATE_DOWN ; 
 int /*<<< orphan*/  TOYOTA_MAX_RATE_UP ; 
 int /*<<< orphan*/  TOYOTA_MAX_RT_DELTA ; 
 int /*<<< orphan*/  TOYOTA_MAX_TORQUE ; 
 int /*<<< orphan*/  TOYOTA_MAX_TORQUE_ERROR ; 
 int /*<<< orphan*/  TOYOTA_MIN_ACCEL ; 
 scalar_t__ TOYOTA_RT_INTERVAL ; 
 scalar_t__ controls_allowed ; 
 int dist_to_meas_check (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_ts_elapsed (scalar_t__,scalar_t__) ; 
 int max_limit_check (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt_rate_limit_check (int,int,int /*<<< orphan*/ ) ; 
 int to_signed (int,int) ; 
 scalar_t__ toyota_actuation_limits ; 
 int toyota_desired_torque_last ; 
 int toyota_rt_torque_last ; 
 int /*<<< orphan*/  toyota_torque_meas ; 
 scalar_t__ toyota_ts_last ; 

__attribute__((used)) static int toyota_tx_hook(CAN_FIFOMailBox_TypeDef *to_send) {

  // Check if msg is sent on BUS 0
  if (((to_send->RDTR >> 4) & 0xF) == 0) {

    // no IPAS in non IPAS mode
    if (((to_send->RIR>>21) == 0x266) || ((to_send->RIR>>21) == 0x167)) return false;

    // GAS PEDAL: safety check
    if ((to_send->RIR>>21) == 0x200) {
      if (controls_allowed && toyota_actuation_limits) {
        // all messages are fine here
      } else {
        if ((to_send->RDLR & 0xFFFF0000) != to_send->RDLR) return 0;
      }
    }

    // ACCEL: safety check on byte 1-2
    if ((to_send->RIR>>21) == 0x343) {
      int desired_accel = ((to_send->RDLR & 0xFF) << 8) | ((to_send->RDLR >> 8) & 0xFF);
      desired_accel = to_signed(desired_accel, 16);
      if (controls_allowed && toyota_actuation_limits) {
        int violation = max_limit_check(desired_accel, TOYOTA_MAX_ACCEL, TOYOTA_MIN_ACCEL);
        if (violation) return 0;
      } else if (!controls_allowed && (desired_accel != 0)) {
        return 0;
      }
    }

    // STEER: safety check on bytes 2-3
    if ((to_send->RIR>>21) == 0x2E4) {
      int desired_torque = (to_send->RDLR & 0xFF00) | ((to_send->RDLR >> 16) & 0xFF);
      desired_torque = to_signed(desired_torque, 16);
      int violation = 0;

      uint32_t ts = TIM2->CNT;

      // only check if controls are allowed and actuation_limits are imposed
      if (controls_allowed && toyota_actuation_limits) {

        // *** global torque limit check ***
        violation |= max_limit_check(desired_torque, TOYOTA_MAX_TORQUE, -TOYOTA_MAX_TORQUE);

        // *** torque rate limit check ***
        violation |= dist_to_meas_check(desired_torque, toyota_desired_torque_last,
          &toyota_torque_meas, TOYOTA_MAX_RATE_UP, TOYOTA_MAX_RATE_DOWN, TOYOTA_MAX_TORQUE_ERROR);

        // used next time
        toyota_desired_torque_last = desired_torque;

        // *** torque real time rate limit check ***
        violation |= rt_rate_limit_check(desired_torque, toyota_rt_torque_last, TOYOTA_MAX_RT_DELTA);

        // every RT_INTERVAL set the new limits
        uint32_t ts_elapsed = get_ts_elapsed(ts, toyota_ts_last);
        if (ts_elapsed > TOYOTA_RT_INTERVAL) {
          toyota_rt_torque_last = desired_torque;
          toyota_ts_last = ts;
        }
      }

      // no torque if controls is not allowed
      if (!controls_allowed && (desired_torque != 0)) {
        violation = 1;
      }

      // reset to 0 if either controls is not allowed or there's a violation
      if (violation || !controls_allowed) {
        toyota_desired_torque_last = 0;
        toyota_rt_torque_last = 0;
        toyota_ts_last = ts;
      }

      if (violation) {
        return false;
      }
    }
  }

  // 1 allows the message through
  return true;
}