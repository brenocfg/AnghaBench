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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  storage_get_block_count () ; 
 int /*<<< orphan*/  storage_get_block_size () ; 

int8_t FLASH_STORAGE_GetCapacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size) {
    *block_size = storage_get_block_size();
    *block_num = storage_get_block_count();
    return 0;
}