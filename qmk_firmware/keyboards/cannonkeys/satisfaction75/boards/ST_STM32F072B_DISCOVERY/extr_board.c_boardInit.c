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
struct TYPE_2__ {int /*<<< orphan*/  CFGR1; } ;

/* Variables and functions */
 TYPE_1__* SYSCFG ; 
 int /*<<< orphan*/  SYSCFG_CFGR1_I2C1_DMA_RMP ; 
 int /*<<< orphan*/  SYSCFG_CFGR1_SPI2_DMA_RMP ; 

void boardInit(void) {
  SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C1_DMA_RMP;
  SYSCFG->CFGR1 &= ~(SYSCFG_CFGR1_SPI2_DMA_RMP);
}