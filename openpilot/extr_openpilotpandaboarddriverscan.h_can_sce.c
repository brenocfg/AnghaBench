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
struct TYPE_5__ {int MSR; int ESR; int /*<<< orphan*/  TSR; } ;
typedef  TYPE_1__ CAN_TypeDef ;

/* Variables and functions */
 size_t BUS_NUM_FROM_CAN_NUM (size_t) ; 
 int CAN_ESR_LEC ; 
 int CAN_MSR_ERRI ; 
 int CAN_MSR_WKUI ; 
 size_t CAN_NUM_FROM_CANIF (TYPE_1__*) ; 
 int /*<<< orphan*/  CAN_TSR_ABRQ0 ; 
 scalar_t__* can_autobaud_enabled ; 
 int /*<<< orphan*/  can_autobaud_speed_increment (size_t) ; 
 int can_err_cnt ; 
 int /*<<< orphan*/  can_set_speed (size_t) ; 
 int /*<<< orphan*/  enter_critical_section () ; 
 int /*<<< orphan*/  exit_critical_section () ; 
 int /*<<< orphan*/  set_can_enable (TYPE_1__*,int) ; 

void can_sce(CAN_TypeDef *CAN) {
  enter_critical_section();

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

  uint8_t can_number = CAN_NUM_FROM_CANIF(CAN);
  uint8_t bus_number = BUS_NUM_FROM_CAN_NUM(can_number);

  if (CAN->MSR & CAN_MSR_WKUI) {
    //Waking from sleep
    #ifdef DEBUG
      puts("WAKE\n");
    #endif
    set_can_enable(CAN, 1);
    CAN->MSR &= ~(CAN_MSR_WKUI);
    CAN->MSR = CAN->MSR;
#ifdef PANDA
    power_save_reset_timer();
#endif
  } else {
    can_err_cnt += 1;


    if (can_autobaud_enabled[bus_number] && (CAN->ESR & CAN_ESR_LEC)) {
      can_autobaud_speed_increment(can_number);
      can_set_speed(can_number);
    }

    // clear current send
    CAN->TSR |= CAN_TSR_ABRQ0;
    CAN->MSR &= ~(CAN_MSR_ERRI);
    CAN->MSR = CAN->MSR;
  }
  exit_critical_section();
}