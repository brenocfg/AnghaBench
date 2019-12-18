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
typedef  int /*<<< orphan*/  DRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  RES_OK ; 
 int /*<<< orphan*/  STA_NOINIT ; 
 int /*<<< orphan*/  sflash_init_done ; 

DRESULT sflash_disk_status(void) {
    if (!sflash_init_done) {
        return STA_NOINIT;
    }
    return RES_OK;
}