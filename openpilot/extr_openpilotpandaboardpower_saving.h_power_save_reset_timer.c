#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ CNT; } ;

/* Variables and functions */
 scalar_t__ POWER_SAVE_STATUS_DISABLED ; 
 TYPE_1__* TIM6 ; 
 int /*<<< orphan*/  power_save_disable () ; 
 scalar_t__ power_save_status ; 

void power_save_reset_timer() {
  TIM6->CNT = 0;
  if (power_save_status != POWER_SAVE_STATUS_DISABLED){
    power_save_disable();
  }
}