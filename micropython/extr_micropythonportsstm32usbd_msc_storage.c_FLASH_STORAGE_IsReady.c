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
typedef  int int8_t ;

/* Variables and functions */
 scalar_t__ flash_started ; 

int8_t FLASH_STORAGE_IsReady(uint8_t lun) {
    if (flash_started) {
        return 0;
    }
    return -1;
}