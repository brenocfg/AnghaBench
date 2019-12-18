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
 scalar_t__ MBOOT_SPIFLASH2_ADDR ; 
 scalar_t__ MBOOT_SPIFLASH2_BYTE_SIZE ; 
 int /*<<< orphan*/  MBOOT_SPIFLASH2_SPIFLASH ; 
 scalar_t__ MBOOT_SPIFLASH_ADDR ; 
 scalar_t__ MBOOT_SPIFLASH_BYTE_SIZE ; 
 int /*<<< orphan*/  MBOOT_SPIFLASH_SPIFLASH ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  mp_spiflash_read (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 

void do_read(uint32_t addr, int len, uint8_t *buf) {
    #if defined(MBOOT_SPIFLASH_ADDR)
    if (MBOOT_SPIFLASH_ADDR <= addr && addr < MBOOT_SPIFLASH_ADDR + MBOOT_SPIFLASH_BYTE_SIZE) {
        mp_spiflash_read(MBOOT_SPIFLASH_SPIFLASH, addr - MBOOT_SPIFLASH_ADDR, len, buf);
        return;
    }
    #endif
    #if defined(MBOOT_SPIFLASH2_ADDR)
    if (MBOOT_SPIFLASH2_ADDR <= addr && addr < MBOOT_SPIFLASH2_ADDR + MBOOT_SPIFLASH2_BYTE_SIZE) {
        mp_spiflash_read(MBOOT_SPIFLASH2_SPIFLASH, addr - MBOOT_SPIFLASH2_ADDR, len, buf);
        return;
    }
    #endif

    // Other addresses, just read directly from memory
    memcpy(buf, (void*)addr, len);
}