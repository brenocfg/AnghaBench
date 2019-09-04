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
typedef  int uint8_t ;
struct TYPE_3__ {int RIR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 scalar_t__ toyota_camera_forwarded ; 
 int /*<<< orphan*/  toyota_giraffe_switch_1 ; 

__attribute__((used)) static int toyota_fwd_hook(int bus_num, CAN_FIFOMailBox_TypeDef *to_fwd) {

  // forward cam to radar and viceversa if car, except lkas cmd and hud
  // don't forward when switch 1 is high
  if ((bus_num == 0 || bus_num == 2) && toyota_camera_forwarded && !toyota_giraffe_switch_1) {
    int addr = to_fwd->RIR>>21;
    bool is_lkas_msg = (addr == 0x2E4 || addr == 0x412) && bus_num == 2;
    return is_lkas_msg? -1 : (uint8_t)(~bus_num & 0x2);
  }
  return -1;
}