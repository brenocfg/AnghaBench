#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* pin; } ;
struct TYPE_8__ {TYPE_2__ interruptData; } ;
typedef  TYPE_3__ pwm2_module_data_t ;
struct TYPE_6__ {scalar_t__ currentInterruptCounter; } ;

/* Variables and functions */
 int GPIO_PIN_NUM ; 
 scalar_t__ isPinSetup (TYPE_3__*,int) ; 

__attribute__((used)) static void resetPinCounters(pwm2_module_data_t *moduleData) {
  for (int i = 1; i < GPIO_PIN_NUM; i++) {
    if (isPinSetup(moduleData, i)) {
      moduleData->interruptData.pin[i].currentInterruptCounter = 0;
    }
  }
}