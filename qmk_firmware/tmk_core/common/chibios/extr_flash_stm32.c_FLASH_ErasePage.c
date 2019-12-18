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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int SR; int /*<<< orphan*/  CR; int /*<<< orphan*/  AR; } ;
typedef  scalar_t__ FLASH_Status ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EraseTimeout ; 
 TYPE_1__* FLASH ; 
 scalar_t__ FLASH_COMPLETE ; 
 int /*<<< orphan*/  FLASH_CR_PER ; 
 int /*<<< orphan*/  FLASH_CR_STRT ; 
 int FLASH_SR_EOP ; 
 int FLASH_SR_PGERR ; 
 int FLASH_SR_WRPERR ; 
 scalar_t__ FLASH_TIMEOUT ; 
 scalar_t__ FLASH_WaitForLastOperation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_FLASH_ADDRESS (int /*<<< orphan*/ ) ; 

FLASH_Status FLASH_ErasePage(uint32_t Page_Address) {
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    ASSERT(IS_FLASH_ADDRESS(Page_Address));
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    if (status == FLASH_COMPLETE) {
        /* if the previous operation is completed, proceed to erase the page */
        FLASH->CR |= FLASH_CR_PER;
        FLASH->AR = Page_Address;
        FLASH->CR |= FLASH_CR_STRT;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(EraseTimeout);
        if (status != FLASH_TIMEOUT) {
            /* if the erase operation is completed, disable the PER Bit */
            FLASH->CR &= ~FLASH_CR_PER;
        }
        FLASH->SR = (FLASH_SR_EOP | FLASH_SR_PGERR | FLASH_SR_WRPERR);
    }
    /* Return the Erase Status */
    return status;
}