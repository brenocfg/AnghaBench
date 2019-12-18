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
 int /*<<< orphan*/  honda_fwd_brake ; 
 scalar_t__ long_controls_allowed ; 

__attribute__((used)) static int honda_fwd_hook(int bus_num, CAN_FIFOMailBox_TypeDef *to_fwd) {
  // fwd from car to camera. also fwd certain msgs from camera to car
  // 0xE4 is steering on all cars except CRV and RDX, 0x194 for CRV and RDX,
  // 0x1FA is brake control, 0x30C is acc hud, 0x33D is lkas hud,
  // 0x39f is radar hud
  int bus_fwd = -1;

  if (bus_num == 0) {
    bus_fwd = 2;
  }
  if (bus_num == 2) {
    // block stock lkas messages and stock acc messages (if OP is doing ACC)
    int addr = GET_ADDR(to_fwd);
    bool is_lkas_msg = (addr == 0xE4) || (addr == 0x194) || (addr == 0x33D);
    bool is_acc_hud_msg = (addr == 0x30C) || (addr == 0x39F);
    bool is_brake_msg = addr == 0x1FA;
    bool block_fwd = is_lkas_msg ||
                     (is_acc_hud_msg && long_controls_allowed) ||
                     (is_brake_msg && long_controls_allowed && !honda_fwd_brake);
    if (!block_fwd) {
      bus_fwd = 0;
    }
  }
  return bus_fwd;
}