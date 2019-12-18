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
 scalar_t__ long_controls_allowed ; 
 scalar_t__ toyota_camera_forwarded ; 
 int /*<<< orphan*/  toyota_giraffe_switch_1 ; 

__attribute__((used)) static int toyota_fwd_hook(int bus_num, CAN_FIFOMailBox_TypeDef *to_fwd) {

  int bus_fwd = -1;
  if (toyota_camera_forwarded && !toyota_giraffe_switch_1) {
    if (bus_num == 0) {
      bus_fwd = 2;
    }
    if (bus_num == 2) {
      int addr = GET_ADDR(to_fwd);
      // block stock lkas messages and stock acc messages (if OP is doing ACC)
      // in TSS2, 0.191 is LTA which we need to block to avoid controls collision
      int is_lkas_msg = ((addr == 0x2E4) || (addr == 0x412) || (addr == 0x191));
      // in TSS2 the camera does ACC as well, so filter 0x343
      int is_acc_msg = (addr == 0x343);
      int block_msg = is_lkas_msg || (is_acc_msg && long_controls_allowed);
      if (!block_msg) {
        bus_fwd = 0;
      }
    }
  }
  return bus_fwd;
}