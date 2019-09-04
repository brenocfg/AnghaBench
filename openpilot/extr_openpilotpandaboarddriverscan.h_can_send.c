#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_5__ {int RDTR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 size_t BUS_MAX ; 
 int /*<<< orphan*/  CAN_NUM_FROM_BUS_NUM (size_t) ; 
 int /*<<< orphan*/ * can_autobaud_enabled ; 
 int* can_num_lookup ; 
 int /*<<< orphan*/  can_push (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * can_queues ; 
 int /*<<< orphan*/  process_can (int /*<<< orphan*/ ) ; 
 scalar_t__ safety_tx_hook (TYPE_1__*) ; 

void can_send(CAN_FIFOMailBox_TypeDef *to_push, uint8_t bus_number) {
  if (safety_tx_hook(to_push) && !can_autobaud_enabled[bus_number]) {
    if (bus_number < BUS_MAX) {
      // add CAN packet to send queue
      // bus number isn't passed through
      to_push->RDTR &= 0xF;
      if (bus_number == 3 && can_num_lookup[3] == 0xFF) {
        #ifdef PANDA
        // TODO: why uint8 bro? only int8?
        bitbang_gmlan(to_push);
        #endif
      } else {
        can_push(can_queues[bus_number], to_push);
        process_can(CAN_NUM_FROM_BUS_NUM(bus_number));
      }
    }
  }
}