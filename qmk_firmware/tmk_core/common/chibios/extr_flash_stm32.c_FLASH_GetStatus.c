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
struct TYPE_2__ {int SR; } ;
typedef  int /*<<< orphan*/  FLASH_Status ;

/* Variables and functions */
 TYPE_1__* FLASH ; 
 int /*<<< orphan*/  FLASH_BUSY ; 
 int /*<<< orphan*/  FLASH_COMPLETE ; 
 int /*<<< orphan*/  FLASH_ERROR_OPT ; 
 int /*<<< orphan*/  FLASH_ERROR_PG ; 
 int /*<<< orphan*/  FLASH_ERROR_WRP ; 
 int FLASH_OBR_OPTERR ; 
 int FLASH_SR_BSY ; 
 int FLASH_SR_PGERR ; 
 int FLASH_SR_WRPERR ; 

FLASH_Status FLASH_GetStatus(void) {
    if ((FLASH->SR & FLASH_SR_BSY) == FLASH_SR_BSY) return FLASH_BUSY;

    if ((FLASH->SR & FLASH_SR_PGERR) != 0) return FLASH_ERROR_PG;

    if ((FLASH->SR & FLASH_SR_WRPERR) != 0) return FLASH_ERROR_WRP;

    if ((FLASH->SR & FLASH_OBR_OPTERR) != 0) return FLASH_ERROR_OPT;

    return FLASH_COMPLETE;
}