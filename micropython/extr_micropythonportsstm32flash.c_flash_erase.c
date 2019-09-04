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
typedef  int uint32_t ;
struct TYPE_3__ {void* Sector; void* NbSectors; int /*<<< orphan*/  VoltageRange; int /*<<< orphan*/  TypeErase; } ;
typedef  TYPE_1__ FLASH_EraseInitTypeDef ;

/* Variables and functions */
 int FLASH_FLAG_EOP ; 
 int FLASH_FLAG_OPERR ; 
 int FLASH_FLAG_PGAERR ; 
 int FLASH_FLAG_PGPERR ; 
 int FLASH_FLAG_PGSERR ; 
 int FLASH_FLAG_WRPERR ; 
 scalar_t__ HAL_FLASHEx_Erase (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  HAL_FLASH_Lock () ; 
 int /*<<< orphan*/  HAL_FLASH_Unlock () ; 
 scalar_t__ HAL_OK ; 
 int /*<<< orphan*/  TYPEERASE_SECTORS ; 
 int /*<<< orphan*/  VOLTAGE_RANGE_3 ; 
 int /*<<< orphan*/  __HAL_FLASH_CLEAR_FLAG (int) ; 
 void* flash_get_sector_info (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void flash_erase(uint32_t flash_dest, uint32_t num_word32) {
    // check there is something to write
    if (num_word32 == 0) {
        return;
    }

    // unlock
    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef EraseInitStruct;

    #if defined(STM32F0)
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGERR);
    EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.PageAddress = flash_dest;
    EraseInitStruct.NbPages     = (4 * num_word32 + FLASH_PAGE_SIZE - 4) / FLASH_PAGE_SIZE;
    #elif  (defined(STM32L4) && !defined(SYSCFG_MEMRMP_FB_MODE))
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);
    EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.Page        = get_page(flash_dest);
    EraseInitStruct.NbPages     = (4 * num_word32 + FLASH_PAGE_SIZE - 4) / FLASH_PAGE_SIZE;
    #elif defined(STM32L4)
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);

    // erase the sector(s)
    // The sector returned by flash_get_sector_info can not be used
    // as the flash has on each bank 0/1 pages 0..255
    EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.Banks       = get_bank(flash_dest);
    EraseInitStruct.Page        = get_page(flash_dest);
    EraseInitStruct.NbPages     = get_page(flash_dest + 4 * num_word32 - 1) - EraseInitStruct.Page + 1;;
    #else
    // Clear pending flags (if any)
    #if defined(STM32H7)
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS_BANK1 | FLASH_FLAG_ALL_ERRORS_BANK2);
    #else
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                           FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
    #endif

    // erase the sector(s)
    EraseInitStruct.TypeErase = TYPEERASE_SECTORS;
    EraseInitStruct.VoltageRange = VOLTAGE_RANGE_3; // voltage range needs to be 2.7V to 3.6V
    #if defined(STM32H7)
    EraseInitStruct.Banks = get_bank(flash_dest);
    #endif
    EraseInitStruct.Sector = flash_get_sector_info(flash_dest, NULL, NULL);
    EraseInitStruct.NbSectors = flash_get_sector_info(flash_dest + 4 * num_word32 - 1, NULL, NULL) - EraseInitStruct.Sector + 1;
    #endif

    uint32_t SectorError = 0;
    if (HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) != HAL_OK) {
        // error occurred during sector erase
        HAL_FLASH_Lock(); // lock the flash
        return;
    }
}