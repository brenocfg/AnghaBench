#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ type; int addr; } ;
typedef  TYPE_1__ partition_item_t ;
typedef  int /*<<< orphan*/  header ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DATA_SIZE ; 
 int INTERNAL_FLASH_SECTOR_SIZE ; 
 scalar_t__ PLATFORM_OK ; 
 int /*<<< orphan*/  PLATFORM_RCR_PHY_DATA ; 
 scalar_t__ SYSTEM_PARTITION_PHY_DATA ; 
 int /*<<< orphan*/  init_data ; 
 int /*<<< orphan*/  os_printf (char*,int) ; 
 scalar_t__ platform_flash_erase_sector (int) ; 
 int /*<<< orphan*/  platform_rcr_write (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_s_flash_read (int*,int,int) ; 
 int /*<<< orphan*/  platform_s_flash_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phy_data_setup (partition_item_t *pt, uint32_t n) {
    uint8_t  header[sizeof(uint32_t)] = {0};
    int i;

    for (i = 0; i < n; i++) {
        if (pt[i].type == SYSTEM_PARTITION_PHY_DATA) {
            uint32_t addr = pt[i].addr;
            platform_s_flash_read(header, addr, sizeof(header));
            if (header[0] != 0x05) {
                uint32_t sector = pt[i].addr/INTERNAL_FLASH_SECTOR_SIZE;
                if (platform_flash_erase_sector(sector) == PLATFORM_OK) {
                    os_printf("Writing Init Data to 0x%08x\n",addr);
                    platform_s_flash_write(init_data, addr, INIT_DATA_SIZE);
                }
            }
            // flag setup complete so we don't retry this every boot
            platform_rcr_write(PLATFORM_RCR_PHY_DATA, &addr, 0);
            return;
        }
    }
    // If the PHY_DATA doesn't exist or the write fails then the
    // SDK will raise the rf_cal error anyway, so just return.
}