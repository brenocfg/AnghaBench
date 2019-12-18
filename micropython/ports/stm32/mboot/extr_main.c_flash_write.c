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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ const uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ base_address; scalar_t__ sector_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLASH_TYPEPROGRAM_FLASHWORD ; 
 scalar_t__ HAL_FLASH_Program (int /*<<< orphan*/ ,scalar_t__,scalar_t__ const) ; 
 int /*<<< orphan*/  HAL_FLASH_Unlock () ; 
 scalar_t__ HAL_OK ; 
 int /*<<< orphan*/  TYPEPROGRAM_WORD ; 
 TYPE_1__* flash_layout ; 

__attribute__((used)) static int flash_write(uint32_t addr, const uint8_t *src8, size_t len) {
    if (addr >= flash_layout[0].base_address && addr < flash_layout[0].base_address + flash_layout[0].sector_size) {
        // Don't allow to write the sector with this bootloader in it
        return -1;
    }

    const uint32_t *src = (const uint32_t*)src8;
    size_t num_word32 = (len + 3) / 4;
    HAL_FLASH_Unlock();

    #if defined(STM32H7)

    // program the flash 256 bits at a time
    for (int i = 0; i < num_word32 / 8; ++i) {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, addr, (uint64_t)(uint32_t)src) != HAL_OK) {
            return - 1;
        }
        addr += 32;
        src += 8;
    }

    #else

    // program the flash word by word
    for (size_t i = 0; i < num_word32; i++) {
        if (HAL_FLASH_Program(TYPEPROGRAM_WORD, addr, *src) != HAL_OK) {
            return -1;
        }
        addr += 4;
        src += 1;
    }

    #endif

    // TODO verify data

    return 0;
}