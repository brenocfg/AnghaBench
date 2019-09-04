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
typedef  int uint32_t ;
struct TYPE_3__ {int RDTR; int RIR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */

__attribute__((used)) static int elm327_tx_hook(CAN_FIFOMailBox_TypeDef *to_send) {
  //All ELM traffic must appear on CAN0
  if(((to_send->RDTR >> 4) & 0xf) != 0) return 0;
  //All ISO 15765-4 messages must be 8 bytes long
  if((to_send->RDTR & 0xf) != 8) return 0;

  if(to_send->RIR & 4){
    uint32_t addr = to_send->RIR >> 3;
    //Check valid 29 bit send addresses for ISO 15765-4
    if(!(addr == 0x18DB33F1 || (addr & 0x1FFF00FF) == 0x18DA00F1)) return 0;
  } else {
    uint32_t addr = to_send->RIR >> 21;
    //Check valid 11 bit send addresses for ISO 15765-4
    if(!(addr == 0x7DF || (addr & 0x7F8) == 0x7E0)) return 0;
  }

  return true;
}