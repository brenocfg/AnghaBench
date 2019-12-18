#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint8_t ;
struct TYPE_6__ {int RDTR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 unsigned int BUS_MAX ; 
 int /*<<< orphan*/  CAN_NUM_FROM_BUS_NUM (unsigned int) ; 
 scalar_t__ bitbang_gmlan (TYPE_1__*) ; 
 unsigned int can_fwd_errs ; 
 int* can_num_lookup ; 
 scalar_t__ can_push (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * can_queues ; 
 unsigned int gmlan_send_errs ; 
 int /*<<< orphan*/  process_can (int /*<<< orphan*/ ) ; 
 scalar_t__ safety_tx_hook (TYPE_1__*) ; 

void can_send(CAN_FIFOMailBox_TypeDef *to_push, uint8_t bus_number) {
  if (safety_tx_hook(to_push) != 0) {
    if (bus_number < BUS_MAX) {
      // add CAN packet to send queue
      // bus number isn't passed through
      to_push->RDTR &= 0xF;
      if ((bus_number == 3U) && (can_num_lookup[3] == 0xFFU)) {
        gmlan_send_errs += bitbang_gmlan(to_push) ? 0U : 1U;
      } else {
        can_fwd_errs += can_push(can_queues[bus_number], to_push) ? 0U : 1U;
        process_can(CAN_NUM_FROM_BUS_NUM(bus_number));
      }
    }
  }
}