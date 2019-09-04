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

/* Variables and functions */
 int /*<<< orphan*/  NVMEM_RM_FILEID ; 
 int /*<<< orphan*/  NVMEM_WLAN_DRIVER_SP_FILEID ; 
 int /*<<< orphan*/  NVMEM_WLAN_FW_SP_FILEID ; 
 int /*<<< orphan*/ * aFATEntries ; 
 int* cMacFromEeprom ; 
 unsigned char* cRMParamsFromEeprom ; 
 scalar_t__ cRMdefaultParams ; 
 int counter ; 
 int /*<<< orphan*/  drv_length ; 
 int fat_write_content (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_length ; 
 int /*<<< orphan*/  fw_patch ; 
 int /*<<< orphan*/  initDriver (int) ; 
 scalar_t__ mac_status ; 
 scalar_t__ nvmem_get_mac_address (int*) ; 
 int nvmem_read (int /*<<< orphan*/ ,int,int,unsigned char*) ; 
 int nvmem_set_mac_address (int*) ; 
 int nvmem_write (int /*<<< orphan*/ ,int,int,unsigned char*) ; 
 int nvmem_write_patch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int return_status ; 
 int /*<<< orphan*/  systick_sleep (int) ; 
 int ucStatus_Dr ; 
 int ucStatus_FW ; 
 int /*<<< orphan*/  wlan_drv_patch ; 
 int /*<<< orphan*/  wlan_stop () ; 

void patch_prog_start()
{
    unsigned short  index;
    unsigned char   *pRMParams;

    printf("Initializing module...\n");

    // Init module and request to load with no patches.
    // This is in order to overwrite restrictions to
    // write to specific places in EEPROM.
    initDriver(1);

    // Read MAC address.
    mac_status = nvmem_get_mac_address(cMacFromEeprom);

    return_status = 1;

    printf("Reading RM parameters...\n");
    while ((return_status) && (counter < 3)) {
        // Read RM parameters.
        // Read in 16 parts to work with tiny driver.
        return_status = 0;
        pRMParams = cRMParamsFromEeprom;
        for (index = 0; index < 16; index++) {
            return_status |= nvmem_read(NVMEM_RM_FILEID, 8, 8*index, pRMParams);
            pRMParams += 8;
        }
        counter++;
    }

    // If RM file is not valid, load the default one.
    if (counter == 3) {
        printf("RM is not valid, loading default one...\n");
        pRMParams = (unsigned char *)cRMdefaultParams;
    } else {
        printf("RM is valid.\n");
        pRMParams = cRMParamsFromEeprom;
    }

    return_status = 1;

    printf("Writing new FAT\n");
    while (return_status) {
        // Write new FAT.
        return_status = fat_write_content(aFATEntries[0], aFATEntries[1]);
    }

    return_status = 1;

    printf("Writing RM parameters...\n");
    while (return_status) {
        // Write RM parameters.
        // Write in 4 parts to work with tiny driver.
        return_status = 0;

        for (index = 0; index < 4; index++) {
            return_status |= nvmem_write(NVMEM_RM_FILEID,
                                         32,
                                         32*index,
                                         (pRMParams + 32*index)); 
        }
    }

    return_status = 1;

    // Write back the MAC address, only if exists.
    if (mac_status == 0) {
        // Zero out MCAST bit if set.
        cMacFromEeprom[0] &= 0xfe;
        printf("Writing back MAC address..\n");
        while (return_status) {
            return_status = nvmem_set_mac_address(cMacFromEeprom);
        }
    }

    // Update driver
    ucStatus_Dr = 1;
    printf("Updating driver patch...\n");
    while (ucStatus_Dr) {
        // Writing driver patch to EEPRROM - PROTABLE CODE
        // Note that the array itself is changing between the
        // different Service Packs.
        ucStatus_Dr = nvmem_write_patch(NVMEM_WLAN_DRIVER_SP_FILEID,
                                        drv_length,
                                        wlan_drv_patch);
    }

    // Update firmware
    ucStatus_FW = 1;
    printf("Updating firmware patch...\n");
    while (ucStatus_FW) {
        // Writing FW patch to EEPRROM - PROTABLE CODE
        // Note that the array itself is changing between the
        // different Service Packs.
        ucStatus_FW = nvmem_write_patch(NVMEM_WLAN_FW_SP_FILEID,
                                        fw_length,
                                        fw_patch);
    }

    printf("Update complete, resetting module\n"\
           "If this doesn't work, reset manually...\n");

    wlan_stop();
    systick_sleep(500);

    // Re-Init module and request to load with patches.
    initDriver(0);

    // If MAC does not exist, it is recommended
    // that the user will write a valid mac address.
    if (mac_status != 0) {
        printf("MAC address is not valid, please write a new one\n");
    }

    // Patch update done
    printf("All done, call wlan.patch_version()\n");
}