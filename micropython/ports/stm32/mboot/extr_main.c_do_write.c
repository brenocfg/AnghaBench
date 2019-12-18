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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LED0 ; 
 scalar_t__ MBOOT_SPIFLASH2_ADDR ; 
 scalar_t__ MBOOT_SPIFLASH2_BYTE_SIZE ; 
 int /*<<< orphan*/  MBOOT_SPIFLASH2_SPIFLASH ; 
 scalar_t__ MBOOT_SPIFLASH_ADDR ; 
 scalar_t__ MBOOT_SPIFLASH_BYTE_SIZE ; 
 int /*<<< orphan*/  MBOOT_SPIFLASH_SPIFLASH ; 
 int flash_write (scalar_t__,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  led_state (int /*<<< orphan*/ ,int) ; 
 int mp_spiflash_write (int /*<<< orphan*/ ,scalar_t__,size_t,int /*<<< orphan*/  const*) ; 

int do_write(uint32_t addr, const uint8_t *src8, size_t len) {
    static uint32_t led_tog = 0;
    led_state(LED0, (led_tog++) & 4);

    #if defined(MBOOT_SPIFLASH_ADDR)
    if (MBOOT_SPIFLASH_ADDR <= addr && addr < MBOOT_SPIFLASH_ADDR + MBOOT_SPIFLASH_BYTE_SIZE) {
        return mp_spiflash_write(MBOOT_SPIFLASH_SPIFLASH, addr - MBOOT_SPIFLASH_ADDR, len, src8);
    }
    #endif

    #if defined(MBOOT_SPIFLASH2_ADDR)
    if (MBOOT_SPIFLASH2_ADDR <= addr && addr < MBOOT_SPIFLASH2_ADDR + MBOOT_SPIFLASH2_BYTE_SIZE) {
        return mp_spiflash_write(MBOOT_SPIFLASH2_SPIFLASH, addr - MBOOT_SPIFLASH2_ADDR, len, src8);
    }
    #endif

    return flash_write(addr, src8, len);
}