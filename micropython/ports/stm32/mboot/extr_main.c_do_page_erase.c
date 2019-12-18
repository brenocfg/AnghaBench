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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LED0 ; 
 scalar_t__ MBOOT_SPIFLASH2_ADDR ; 
 scalar_t__ MBOOT_SPIFLASH2_BYTE_SIZE ; 
 int MBOOT_SPIFLASH2_ERASE_BLOCKS_PER_PAGE ; 
 int /*<<< orphan*/  MBOOT_SPIFLASH2_SPIFLASH ; 
 scalar_t__ MBOOT_SPIFLASH_ADDR ; 
 scalar_t__ MBOOT_SPIFLASH_BYTE_SIZE ; 
 int MBOOT_SPIFLASH_ERASE_BLOCKS_PER_PAGE ; 
 int /*<<< orphan*/  MBOOT_SPIFLASH_SPIFLASH ; 
 int MP_SPIFLASH_ERASE_BLOCK_SIZE ; 
 int flash_page_erase (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  led_state (int /*<<< orphan*/ ,int) ; 
 int spiflash_page_erase (int /*<<< orphan*/ ,scalar_t__,int) ; 

int do_page_erase(uint32_t addr, uint32_t *next_addr) {
    led_state(LED0, 1);

    #if defined(MBOOT_SPIFLASH_ADDR)
    if (MBOOT_SPIFLASH_ADDR <= addr && addr < MBOOT_SPIFLASH_ADDR + MBOOT_SPIFLASH_BYTE_SIZE) {
        *next_addr = addr + MBOOT_SPIFLASH_ERASE_BLOCKS_PER_PAGE * MP_SPIFLASH_ERASE_BLOCK_SIZE;
        return spiflash_page_erase(MBOOT_SPIFLASH_SPIFLASH,
            addr - MBOOT_SPIFLASH_ADDR, MBOOT_SPIFLASH_ERASE_BLOCKS_PER_PAGE);
    }
    #endif

    #if defined(MBOOT_SPIFLASH2_ADDR)
    if (MBOOT_SPIFLASH2_ADDR <= addr && addr < MBOOT_SPIFLASH2_ADDR + MBOOT_SPIFLASH2_BYTE_SIZE) {
        *next_addr = addr + MBOOT_SPIFLASH2_ERASE_BLOCKS_PER_PAGE * MP_SPIFLASH_ERASE_BLOCK_SIZE;
        return spiflash_page_erase(MBOOT_SPIFLASH2_SPIFLASH,
            addr - MBOOT_SPIFLASH2_ADDR, MBOOT_SPIFLASH2_ERASE_BLOCKS_PER_PAGE);
    }
    #endif

    return flash_page_erase(addr, next_addr);
}