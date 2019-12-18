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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLASH_TYPEPROGRAM_DOUBLEWORD ; 
 int /*<<< orphan*/  FLASH_TYPEPROGRAM_FLASHWORD ; 
 int /*<<< orphan*/  FLASH_TYPEPROGRAM_WORD ; 
 int /*<<< orphan*/  HAL_FLASH_Lock () ; 
 scalar_t__ HAL_FLASH_Program (int /*<<< orphan*/ ,int,int const) ; 
 scalar_t__ HAL_OK ; 

void flash_write(uint32_t flash_dest, const uint32_t *src, uint32_t num_word32) {
    #if defined(STM32L4) || defined(STM32WB)

    // program the flash uint64 by uint64
    for (int i = 0; i < num_word32 / 2; i++) {
        uint64_t val = *(uint64_t*)src;
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, flash_dest, val) != HAL_OK) {
            // error occurred during flash write
            HAL_FLASH_Lock(); // lock the flash
            return;
        }
        flash_dest += 8;
        src += 2;
    }
    if ((num_word32 & 0x01) == 1) {
        uint64_t val = *(uint64_t*)flash_dest;
        val = (val & 0xffffffff00000000uL) | (*src);
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, flash_dest, val) != HAL_OK) {
            // error occurred during flash write
            HAL_FLASH_Lock(); // lock the flash
            return;
        }
    }

    #elif defined(STM32H7)

    // program the flash 256 bits at a time
    for (int i = 0; i < num_word32 / 8; i++) {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, flash_dest, (uint64_t)(uint32_t)src) != HAL_OK) {
            // error occurred during flash write
            HAL_FLASH_Lock(); // lock the flash
            return;
        }
        flash_dest += 32;
        src += 8;
    }

    #else

    // program the flash word by word
    for (int i = 0; i < num_word32; i++) {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, flash_dest, *src) != HAL_OK) {
            // error occurred during flash write
            HAL_FLASH_Lock(); // lock the flash
            return;
        }
        flash_dest += 4;
        src += 1;
    }

    #endif

    // lock the flash
    HAL_FLASH_Lock();
}