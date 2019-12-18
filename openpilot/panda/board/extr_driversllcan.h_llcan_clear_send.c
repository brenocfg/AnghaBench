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
struct TYPE_3__ {int /*<<< orphan*/  MSR; int /*<<< orphan*/  TSR; } ;
typedef  TYPE_1__ CAN_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_MSR_ERRI ; 
 int /*<<< orphan*/  CAN_TSR_ABRQ0 ; 

void llcan_clear_send(CAN_TypeDef *CAN_obj) {
  CAN_obj->TSR |= CAN_TSR_ABRQ0;
  CAN_obj->MSR &= ~(CAN_MSR_ERRI);
  // cppcheck-suppress selfAssignment ; needed to clear the register
  CAN_obj->MSR = CAN_obj->MSR;
}