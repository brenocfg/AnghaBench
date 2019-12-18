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
 int GET_BUS (int /*<<< orphan*/ *) ; 
 int GET_BYTE (int /*<<< orphan*/ *,int) ; 
 scalar_t__ GET_BYTES_04 (int /*<<< orphan*/ *) ; 
 int GET_LEN (int /*<<< orphan*/ *) ; 
 int ignition_can ; 

void ignition_can_hook(CAN_FIFOMailBox_TypeDef *to_push) {

  int bus = GET_BUS(to_push);
  int addr = GET_ADDR(to_push);
  int len = GET_LEN(to_push);

  if (bus == 0) {
    // GM exception
    if ((addr == 0x1F1) && (len == 8)) {
      //Bit 5 is ignition "on"
      ignition_can = (GET_BYTE(to_push, 0) & 0x20) != 0;
    }
    // Tesla exception
    if ((addr == 0x348) && (len == 8)) {
      // GTW_status
      ignition_can = (GET_BYTE(to_push, 0) & 0x1) != 0;
    }
    // Cadillac exception
    if ((addr == 0x160) && (len == 5)) {
      // this message isn't all zeros when ignition is on
      ignition_can = GET_BYTES_04(to_push) != 0;
    }
    // VW exception
    if ((addr == 0x3C0) && (len == 4)) {
     // VW Terminal 15 (ignition-on) state
     ignition_can  = (GET_BYTE(to_push, 2) & 0x2) != 0;
    }
  }
}