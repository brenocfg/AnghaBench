#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 int GET_ADDR (int /*<<< orphan*/ *) ; 
 int MSG_HCA_01 ; 
 int MSG_LDW_02 ; 

__attribute__((used)) static int volkswagen_fwd_hook(int bus_num, CAN_FIFOMailBox_TypeDef *to_fwd) {
  int addr = GET_ADDR(to_fwd);
  int bus_fwd = -1;

  // NOTE: Will need refactoring for other bus layouts, such as no-forwarding at camera or J533 running-gear CAN

  switch (bus_num) {
    case 0:
      // Forward all traffic from J533 gateway to Extended CAN devices.
      bus_fwd = 2;
      break;
    case 2:
      if ((addr == MSG_HCA_01) || (addr == MSG_LDW_02)) {
        // OP takes control of the Heading Control Assist and Lane Departure Warning messages from the camera.
        bus_fwd = -1;
      } else {
        // Forward all remaining traffic from Extended CAN devices to J533 gateway.
        bus_fwd = 0;
      }
      break;
    default:
      // No other buses should be in use; fallback to do-not-forward.
      bus_fwd = -1;
      break;
  }

  return bus_fwd;
}