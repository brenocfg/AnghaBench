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
 int GET_LEN (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int elm327_tx_hook(CAN_FIFOMailBox_TypeDef *to_send) {

  int tx = 1;
  int addr = GET_ADDR(to_send);
  int len = GET_LEN(to_send);

  //All ISO 15765-4 messages must be 8 bytes long
  if (len != 8) {
    tx = 0;
  }

  //Check valid 29 bit send addresses for ISO 15765-4
  //Check valid 11 bit send addresses for ISO 15765-4
  if ((addr != 0x18DB33F1) && ((addr & 0x1FFF00FF) != 0x18DA00F1) &&
      ((addr != 0x7DF) && ((addr & 0x7F8) != 0x7E0))) {
    tx = 0;
  }
  return tx;
}