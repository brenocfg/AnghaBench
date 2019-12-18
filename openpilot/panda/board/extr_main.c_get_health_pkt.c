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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__ (* check_ignition ) () ;int /*<<< orphan*/  (* read_current ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  adc_get_voltage () ; 
 int /*<<< orphan*/  can_fwd_errs ; 
 int /*<<< orphan*/  can_send_errs ; 
 void* car_harness_status ; 
 void* controls_allowed ; 
 TYPE_1__* current_board ; 
 scalar_t__ current_safety_mode ; 
 void* gas_interceptor_detected ; 
 int /*<<< orphan*/  gmlan_send_errs ; 
 scalar_t__ ignition_can ; 
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ stub2 () ; 
 void* usb_power_mode ; 

int get_health_pkt(void *dat) {
  struct __attribute__((packed)) {
    uint32_t voltage_pkt;
    uint32_t current_pkt;
    uint32_t can_send_errs_pkt;
    uint32_t can_fwd_errs_pkt;
    uint32_t gmlan_send_errs_pkt;
    uint8_t ignition_line_pkt;
    uint8_t ignition_can_pkt;
    uint8_t controls_allowed_pkt;
    uint8_t gas_interceptor_detected_pkt;
    uint8_t car_harness_status_pkt;
    uint8_t usb_power_mode_pkt;
    uint8_t safety_mode_pkt;
  } *health = dat;

  health->voltage_pkt = adc_get_voltage();
  health->current_pkt = current_board->read_current();

  //Use the GPIO pin to determine ignition or use a CAN based logic
  health->ignition_line_pkt = (uint8_t)(current_board->check_ignition());
  health->ignition_can_pkt = (uint8_t)(ignition_can);

  health->controls_allowed_pkt = controls_allowed;
  health->gas_interceptor_detected_pkt = gas_interceptor_detected;
  health->can_send_errs_pkt = can_send_errs;
  health->can_fwd_errs_pkt = can_fwd_errs;
  health->gmlan_send_errs_pkt = gmlan_send_errs;
  health->car_harness_status_pkt = car_harness_status;
  health->usb_power_mode_pkt = usb_power_mode;
  health->safety_mode_pkt = (uint8_t)(current_safety_mode);

  return sizeof(*health);
}