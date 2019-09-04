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
typedef  void* uint32_t ;
struct TYPE_3__ {int RDTR; void* RIR; void* RDLR; void* RDHR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 int CAN_BUS_NUM_MASK ; 
 int /*<<< orphan*/  can_send (TYPE_1__*,int) ; 

void usb_cb_ep3_out(uint8_t *usbdata, int len, int hardwired) {
  int dpkt = 0;
  for (dpkt = 0; dpkt < len; dpkt += 0x10) {
    uint32_t *tf = (uint32_t*)(&usbdata[dpkt]);

    // make a copy
    CAN_FIFOMailBox_TypeDef to_push;
    to_push.RDHR = tf[3];
    to_push.RDLR = tf[2];
    to_push.RDTR = tf[1];
    to_push.RIR = tf[0];

    uint8_t bus_number = (to_push.RDTR >> 4) & CAN_BUS_NUM_MASK;
    can_send(&to_push, bus_number);

    #ifdef PANDA
      // Enable relay on can message if allowed.
      // Temporary until OP has support for relay
      if (safety_relay_hook()) {
        set_lline_output(1);
      }
    #endif
  }
}