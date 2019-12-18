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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  CAN_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/ * CANIF_FROM_CAN_NUM (int) ; 
 int /*<<< orphan*/  can_set_speed (int) ; 
 int /*<<< orphan*/  llcan_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_can (int) ; 

void can_init(uint8_t can_number) {
  if (can_number != 0xffU) {
    CAN_TypeDef *CAN = CANIF_FROM_CAN_NUM(can_number);
    can_set_speed(can_number);

    llcan_init(CAN);

    // in case there are queued up messages
    process_can(can_number);
  }
}