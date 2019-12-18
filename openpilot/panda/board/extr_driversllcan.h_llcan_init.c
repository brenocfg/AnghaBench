#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int FA1R; int IER; int /*<<< orphan*/  FMR; TYPE_1__* sFilterRegister; } ;
struct TYPE_7__ {scalar_t__ FR2; scalar_t__ FR1; } ;
typedef  TYPE_2__ CAN_TypeDef ;

/* Variables and functions */
 TYPE_2__* CAN1 ; 
 int /*<<< orphan*/  CAN1_RX0_IRQn ; 
 int /*<<< orphan*/  CAN1_SCE_IRQn ; 
 int /*<<< orphan*/  CAN1_TX_IRQn ; 
 TYPE_2__* CAN2 ; 
 int /*<<< orphan*/  CAN2_RX0_IRQn ; 
 int /*<<< orphan*/  CAN2_SCE_IRQn ; 
 int /*<<< orphan*/  CAN2_TX_IRQn ; 
 TYPE_2__* CAN3 ; 
 int /*<<< orphan*/  CAN3_RX0_IRQn ; 
 int /*<<< orphan*/  CAN3_SCE_IRQn ; 
 int /*<<< orphan*/  CAN3_TX_IRQn ; 
 int /*<<< orphan*/  CAN_FMR_FINIT ; 
 int CAN_IER_FMPIE0 ; 
 int CAN_IER_TMEIE ; 
 int CAN_IER_WKUIE ; 
 int /*<<< orphan*/  NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char*) ; 

void llcan_init(CAN_TypeDef *CAN_obj) {
  // accept all filter
  CAN_obj->FMR |= CAN_FMR_FINIT;

  // no mask
  CAN_obj->sFilterRegister[0].FR1 = 0;
  CAN_obj->sFilterRegister[0].FR2 = 0;
  CAN_obj->sFilterRegister[14].FR1 = 0;
  CAN_obj->sFilterRegister[14].FR2 = 0;
  CAN_obj->FA1R |= 1U | (1U << 14);

  CAN_obj->FMR &= ~(CAN_FMR_FINIT);

  // enable certain CAN interrupts
  CAN_obj->IER |= CAN_IER_TMEIE | CAN_IER_FMPIE0 |  CAN_IER_WKUIE;

  if (CAN_obj == CAN1) {
    NVIC_EnableIRQ(CAN1_TX_IRQn);
    NVIC_EnableIRQ(CAN1_RX0_IRQn);
    NVIC_EnableIRQ(CAN1_SCE_IRQn);
  } else if (CAN_obj == CAN2) {
    NVIC_EnableIRQ(CAN2_TX_IRQn);
    NVIC_EnableIRQ(CAN2_RX0_IRQn);
    NVIC_EnableIRQ(CAN2_SCE_IRQn);
#ifdef CAN3
  } else if (CAN_obj == CAN3) {
    NVIC_EnableIRQ(CAN3_TX_IRQn);
    NVIC_EnableIRQ(CAN3_RX0_IRQn);
    NVIC_EnableIRQ(CAN3_SCE_IRQn);
#endif
  } else {
    puts("Invalid CAN: initialization failed\n");
  }
}