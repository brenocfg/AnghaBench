#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_10__ {int RDTR; int /*<<< orphan*/  RDHR; int /*<<< orphan*/  RDLR; int /*<<< orphan*/  RIR; } ;
struct TYPE_9__ {int RF0R; TYPE_1__* sFIFOMailBox; } ;
struct TYPE_8__ {int RDTR; int /*<<< orphan*/  RDHR; int /*<<< orphan*/  RDLR; int /*<<< orphan*/  RIR; } ;
typedef  TYPE_2__ CAN_TypeDef ;
typedef  TYPE_3__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 size_t BUS_NUM_FROM_CAN_NUM (size_t) ; 
 TYPE_2__* CANIF_FROM_CAN_NUM (size_t) ; 
 int /*<<< orphan*/  CAN_NAME_FROM_CANIF (TYPE_2__*) ; 
 int CAN_RF0R_FMP0 ; 
 int CAN_RF0R_RFOM0 ; 
 int* can_autobaud_enabled ; 
 int /*<<< orphan*/  can_push (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int can_rx_cnt ; 
 int /*<<< orphan*/  can_rx_q ; 
 int pending_can_live ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safety_rx_hook (TYPE_3__*) ; 

void can_rx(uint8_t can_number) {
  #ifdef PANDA
    power_save_reset_timer();
  #endif
  CAN_TypeDef *CAN = CANIF_FROM_CAN_NUM(can_number);
  uint8_t bus_number = BUS_NUM_FROM_CAN_NUM(can_number);
  while (CAN->RF0R & CAN_RF0R_FMP0) {
    if (can_autobaud_enabled[bus_number]) {
      can_autobaud_enabled[bus_number] = false;
      puts(CAN_NAME_FROM_CANIF(CAN));
    #ifdef DEBUG
      puts(" auto-baud ");
      putui(can_speed[bus_number]);
      puts(" cbps\n");
    #endif
    }

    can_rx_cnt += 1;

    // can is live
    pending_can_live = 1;

    // add to my fifo
    CAN_FIFOMailBox_TypeDef to_push;
    to_push.RIR = CAN->sFIFOMailBox[0].RIR;
    to_push.RDTR = CAN->sFIFOMailBox[0].RDTR;
    to_push.RDLR = CAN->sFIFOMailBox[0].RDLR;
    to_push.RDHR = CAN->sFIFOMailBox[0].RDHR;

    // modify RDTR for our API
    to_push.RDTR = (to_push.RDTR & 0xFFFF000F) | (bus_number << 4);

    // forwarding (panda only)
    #ifdef PANDA
      if ((get_lline_status() != 0) || !relay_control) { //Relay engaged or relay isn't controlled, allow fwd
        int bus_fwd_num = can_forwarding[bus_number] != -1 ? can_forwarding[bus_number] : safety_fwd_hook(bus_number, &to_push);
        if (bus_fwd_num != -1) {
          CAN_FIFOMailBox_TypeDef to_send;
          to_send.RIR = to_push.RIR | 1; // TXRQ
          to_send.RDTR = to_push.RDTR;
          to_send.RDLR = to_push.RDLR;
          to_send.RDHR = to_push.RDHR;
          can_send(&to_send, bus_fwd_num);
        }
      }
    #endif

    safety_rx_hook(&to_push);

    #ifdef PANDA
      set_led(LED_BLUE, 1);
    #endif
    can_push(&can_rx_q, &to_push);

    // next
    CAN->RF0R |= CAN_RF0R_RFOM0;
  }
}