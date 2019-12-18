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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int NbSectors; scalar_t__ Sector; int /*<<< orphan*/  Banks; int /*<<< orphan*/  VoltageRange; int /*<<< orphan*/  TypeErase; } ;
typedef  TYPE_1__ FLASH_EraseInitTypeDef ;

/* Variables and functions */
 int FLASH_FLAG_ALL_ERRORS_BANK1 ; 
 int FLASH_FLAG_ALL_ERRORS_BANK2 ; 
 int FLASH_FLAG_EOP ; 
 int FLASH_FLAG_OPERR ; 
 int FLASH_FLAG_PGAERR ; 
 int FLASH_FLAG_PGPERR ; 
 int FLASH_FLAG_PGSERR ; 
 int FLASH_FLAG_WRPERR ; 
 scalar_t__ HAL_FLASHEx_Erase (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  HAL_FLASH_Unlock () ; 
 scalar_t__ HAL_OK ; 
 int /*<<< orphan*/  TYPEERASE_SECTORS ; 
 int /*<<< orphan*/  VOLTAGE_RANGE_3 ; 
 int /*<<< orphan*/  __HAL_FLASH_CLEAR_FLAG (int) ; 
 scalar_t__ flash_get_sector_index (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  get_bank (scalar_t__) ; 

__attribute__((used)) static int flash_page_erase(uint32_t addr, uint32_t *next_addr) {
    uint32_t sector_size = 0;
    uint32_t sector = flash_get_sector_index(addr, &sector_size);
    if (sector == 0) {
        // Don't allow to erase the sector with this bootloader in it
        return -1;
    }

    *next_addr = addr + sector_size;

    HAL_FLASH_Unlock();

    // Clear pending flags (if any)
    #if defined(STM32H7)
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS_BANK1 | FLASH_FLAG_ALL_ERRORS_BANK2);
    #else
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                           FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
    #endif

    // erase the sector(s)
    FLASH_EraseInitTypeDef EraseInitStruct;
    EraseInitStruct.TypeErase = TYPEERASE_SECTORS;
    EraseInitStruct.VoltageRange = VOLTAGE_RANGE_3; // voltage range needs to be 2.7V to 3.6V
    #if defined(STM32H7)
    EraseInitStruct.Banks = get_bank(addr);
    #endif
    EraseInitStruct.Sector = sector;
    EraseInitStruct.NbSectors = 1;

    uint32_t SectorError = 0;
    if (HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) != HAL_OK) {
        // error occurred during sector erase
        return -1;
    }

    // Check the erase set bits to 1, at least for the first 256 bytes
    for (int i = 0; i < 64; ++i) {
        if (((volatile uint32_t*)addr)[i] != 0xffffffff) {
            return -2;
        }
    }

    return 0;
}