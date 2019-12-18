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
 int GET_ADDR (int /*<<< orphan*/ *) ; 
 int GET_BYTE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TESLA_LOOKUP_ANGLE_RATE_DOWN ; 
 int /*<<< orphan*/  TESLA_LOOKUP_ANGLE_RATE_UP ; 
 scalar_t__ TESLA_RT_INTERVAL ; 
 TYPE_1__* TIM2 ; 
 int controls_allowed ; 
 int eac_status ; 
 scalar_t__ fmax_limit_check (float,float,float) ; 
 scalar_t__ get_ts_elapsed (scalar_t__,scalar_t__) ; 
 int interpolate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_gmlan_switch_timeout () ; 
 int /*<<< orphan*/  set_gmlan_digital_output (int /*<<< orphan*/ ) ; 
 int tesla_controls_allowed_last ; 
 int tesla_rt_angle_last ; 
 int tesla_speed ; 
 scalar_t__ tesla_ts_angle_last ; 

__attribute__((used)) static void tesla_rx_hook(CAN_FIFOMailBox_TypeDef *to_push) {
  set_gmlan_digital_output(0); // #define GMLAN_HIGH 0
  reset_gmlan_switch_timeout(); //we're still in tesla safety mode, reset the timeout counter and make sure our output is enabled

  int addr = GET_ADDR(to_push);

  if (addr == 0x45) {
    // 6 bits starting at position 0
    int lever_position = GET_BYTE(to_push, 0) & 0x3F;
    if (lever_position == 2) { // pull forward
      // activate openpilot
      controls_allowed = 1;
    }
    if (lever_position == 1) { // push towards the back
      // deactivate openpilot
      controls_allowed = 0;
    }
  }

  // exit controls on brake press
  // DI_torque2::DI_brakePedal 0x118
  if (addr == 0x118) {
    // 1 bit at position 16
    if ((GET_BYTE(to_push, 1) & 0x80) != 0) {
      // disable break cancel by commenting line below
      controls_allowed = 0;
    }
    //get vehicle speed in m/s. Tesla gives MPH
    tesla_speed = (((((GET_BYTE(to_push, 3) & 0xF) << 8) + GET_BYTE(to_push, 2)) * 0.05) - 25) * 1.609 / 3.6;
    if (tesla_speed < 0) {
      tesla_speed = 0;
    }
  }

  // exit controls on EPAS error
  // EPAS_sysStatus::EPAS_eacStatus 0x370
  if (addr == 0x370) {
    // if EPAS_eacStatus is not 1 or 2, disable control
    eac_status = (GET_BYTE(to_push, 6) >> 5) & 0x7;
    // For human steering override we must not disable controls when eac_status == 0
    // Additional safety: we could only allow eac_status == 0 when we have human steering allowed
    if (controls_allowed && (eac_status != 0) && (eac_status != 1) && (eac_status != 2)) {
      controls_allowed = 0;
      //puts("EPAS error! \n");
    }
  }
  //get latest steering wheel angle
  if (addr == 0x00E) {
    float angle_meas_now = (int)(((((GET_BYTE(to_push, 0) & 0x3F) << 8) + GET_BYTE(to_push, 1)) * 0.1) - 819.2);
    uint32_t ts = TIM2->CNT;
    uint32_t ts_elapsed = get_ts_elapsed(ts, tesla_ts_angle_last);

    // *** angle real time check
    // add 1 to not false trigger the violation and multiply by 25 since the check is done every 250 ms and steer angle is updated at     100Hz
    float rt_delta_angle_up = (interpolate(TESLA_LOOKUP_ANGLE_RATE_UP, tesla_speed) * 25.) + 1.;
    float rt_delta_angle_down = (interpolate(TESLA_LOOKUP_ANGLE_RATE_DOWN, tesla_speed) * 25.) + 1.;
    float highest_rt_angle = tesla_rt_angle_last + ((tesla_rt_angle_last > 0.) ? rt_delta_angle_up : rt_delta_angle_down);
    float lowest_rt_angle = tesla_rt_angle_last - ((tesla_rt_angle_last > 0.) ? rt_delta_angle_down : rt_delta_angle_up);

    if ((ts_elapsed > TESLA_RT_INTERVAL) || (controls_allowed && !tesla_controls_allowed_last)) {
      tesla_rt_angle_last = angle_meas_now;
      tesla_ts_angle_last = ts;
    }

    // check for violation;
    if (fmax_limit_check(angle_meas_now, highest_rt_angle, lowest_rt_angle)) {
      // We should not be able to STEER under these conditions
      // Other sending is fine (to allow human override)
      controls_allowed = 0;
      //puts("WARN: RT Angle - No steer allowed! \n");
    } else {
      controls_allowed = 1;
    }

    tesla_controls_allowed_last = controls_allowed;
  }
}