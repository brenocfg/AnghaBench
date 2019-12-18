#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ESR; int /*<<< orphan*/  RF1R; int /*<<< orphan*/  RF0R; int /*<<< orphan*/  TSR; int /*<<< orphan*/  MSR; } ;
typedef  TYPE_1__ CAN_TypeDef ;

/* Variables and functions */
 TYPE_1__* CAN1 ; 
 TYPE_1__* CAN2 ; 
 TYPE_1__* CAN3 ; 
 int /*<<< orphan*/  ENTER_CRITICAL () ; 
 int /*<<< orphan*/  EXIT_CRITICAL () ; 
 int can_err_cnt ; 
 int /*<<< orphan*/  llcan_clear_send (TYPE_1__*) ; 
 int /*<<< orphan*/  puth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char*) ; 

void can_sce(CAN_TypeDef *CAN) {
  ENTER_CRITICAL();

  #ifdef DEBUG
    if (CAN==CAN1) puts("CAN1:  ");
    if (CAN==CAN2) puts("CAN2:  ");
    #ifdef CAN3
      if (CAN==CAN3) puts("CAN3:  ");
    #endif
    puts("MSR:");
    puth(CAN->MSR);
    puts(" TSR:");
    puth(CAN->TSR);
    puts(" RF0R:");
    puth(CAN->RF0R);
    puts(" RF1R:");
    puth(CAN->RF1R);
    puts(" ESR:");
    puth(CAN->ESR);
    puts("\n");
  #endif

  can_err_cnt += 1;
  llcan_clear_send(CAN);
  EXIT_CRITICAL();
}