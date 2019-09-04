#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int FA1R; int IER; int /*<<< orphan*/  FMR; TYPE_1__* sFilterRegister; } ;
struct TYPE_5__ {scalar_t__ FR2; scalar_t__ FR1; } ;
typedef  TYPE_2__ CAN_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  CAN1_RX0_IRQn ; 
 int /*<<< orphan*/  CAN1_SCE_IRQn ; 
 int /*<<< orphan*/  CAN1_TX_IRQn ; 
 int /*<<< orphan*/  CAN2_RX0_IRQn ; 
 int /*<<< orphan*/  CAN2_SCE_IRQn ; 
 int /*<<< orphan*/  CAN2_TX_IRQn ; 
 TYPE_2__* CANIF_FROM_CAN_NUM (int) ; 
 int /*<<< orphan*/  CAN_FMR_FINIT ; 
 int CAN_IER_FMPIE0 ; 
 int CAN_IER_TMEIE ; 
 int CAN_IER_WKUIE ; 
 int /*<<< orphan*/  NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_set_speed (int) ; 
 int /*<<< orphan*/  process_can (int) ; 
 int /*<<< orphan*/  set_can_enable (TYPE_2__*,int) ; 

void can_init(uint8_t can_number) {
  if (can_number == 0xff) return;

  CAN_TypeDef *CAN = CANIF_FROM_CAN_NUM(can_number);
  set_can_enable(CAN, 1);
  can_set_speed(can_number);

  // accept all filter
  CAN->FMR |= CAN_FMR_FINIT;

  // no mask
  CAN->sFilterRegister[0].FR1 = 0;
  CAN->sFilterRegister[0].FR2 = 0;
  CAN->sFilterRegister[14].FR1 = 0;
  CAN->sFilterRegister[14].FR2 = 0;
  CAN->FA1R |= 1 | (1 << 14);

  CAN->FMR &= ~(CAN_FMR_FINIT);

  // enable certain CAN interrupts
  CAN->IER |= CAN_IER_TMEIE | CAN_IER_FMPIE0 |  CAN_IER_WKUIE;

  switch (can_number) {
    case 0:
      NVIC_EnableIRQ(CAN1_TX_IRQn);
      NVIC_EnableIRQ(CAN1_RX0_IRQn);
      NVIC_EnableIRQ(CAN1_SCE_IRQn);
      break;
    case 1:
      NVIC_EnableIRQ(CAN2_TX_IRQn);
      NVIC_EnableIRQ(CAN2_RX0_IRQn);
      NVIC_EnableIRQ(CAN2_SCE_IRQn);
      break;
#ifdef CAN3
    case 2:
      NVIC_EnableIRQ(CAN3_TX_IRQn);
      NVIC_EnableIRQ(CAN3_RX0_IRQn);
      NVIC_EnableIRQ(CAN3_SCE_IRQn);
      break;
#endif
  }

  // in case there are queued up messages
  process_can(can_number);
}