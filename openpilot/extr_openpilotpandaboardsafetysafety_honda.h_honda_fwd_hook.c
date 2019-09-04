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
struct TYPE_3__ {int RIR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */

__attribute__((used)) static int honda_fwd_hook(int bus_num, CAN_FIFOMailBox_TypeDef *to_fwd) {
  // fwd from car to camera. also fwd certain msgs from camera to car
  // 0xE4 is steering on all cars except CRV and RDX, 0x194 for CRV and RDX,
  // 0x1FA is brake control, 0x30C is acc hud, 0x33D is lkas hud,
  // 0x39f is radar hud
  int addr = to_fwd->RIR>>21;
  if (bus_num == 0) {
    return 2;
  } else if (bus_num == 2 && addr != 0xE4 && addr != 0x194 && addr != 0x1FA &&
             addr != 0x30C && addr != 0x33D && addr != 0x39F) {
    return 0;
  }

  return -1;
}