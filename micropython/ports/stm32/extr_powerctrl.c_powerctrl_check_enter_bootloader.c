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
typedef  int uint32_t ;
struct TYPE_2__ {int RCC_SR; } ;

/* Variables and functions */
 int* BL_STATE ; 
 TYPE_1__* RCC ; 
 int RCC_SR_RMVF ; 
 int RCC_SR_SFTRSTF ; 
 int /*<<< orphan*/  __HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH () ; 
 int /*<<< orphan*/  branch_to_bootloader (int,int) ; 

void powerctrl_check_enter_bootloader(void) {
    uint32_t bl_addr = BL_STATE[1];
    BL_STATE[1] = 1; // invalidate bootloader address
    if ((bl_addr & 0xfff) == 0 && (RCC->RCC_SR & RCC_SR_SFTRSTF)) {
        // Reset by NVIC_SystemReset with bootloader data set -> branch to bootloader
        RCC->RCC_SR = RCC_SR_RMVF;
        #if defined(STM32F0) || defined(STM32F4) || defined(STM32L0) || defined(STM32L4) || defined(STM32WB)
        __HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH();
        #endif
        uint32_t r0 = BL_STATE[0];
        branch_to_bootloader(r0, bl_addr);
    }
}