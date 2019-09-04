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
 int /*<<< orphan*/  FS_MODE_OPEN_WRITE ; 
 int /*<<< orphan*/  RES_ERROR ; 
 int /*<<< orphan*/  RES_OK ; 
 int /*<<< orphan*/  sflash_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sflash_cache_is_dirty ; 
 int /*<<< orphan*/  sl_FsWrite ; 

DRESULT sflash_disk_flush (void) {
    // Write back the cache if it's dirty
    if (sflash_cache_is_dirty) {
        if (!sflash_access(FS_MODE_OPEN_WRITE, sl_FsWrite)) {
            return RES_ERROR;
        }
        sflash_cache_is_dirty = false;
    }
    return RES_OK;
}