#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_3__ {int RIR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  chrysler_camera_detected ; 

__attribute__((used)) static int chrysler_fwd_hook(int bus_num, CAN_FIFOMailBox_TypeDef *to_fwd) {
  int32_t addr = to_fwd->RIR >> 21;
  // forward CAN 0 -> 2 so stock LKAS camera sees messages
  if (bus_num == 0 && !chrysler_camera_detected) {
    return 2;
  }
  // forward all messages from camera except LKAS_COMMAND and LKAS_HUD
  if (bus_num == 2 && !chrysler_camera_detected && addr != 658 && addr != 678) {
    return 0;
  }
  return -1;  // do not forward
}