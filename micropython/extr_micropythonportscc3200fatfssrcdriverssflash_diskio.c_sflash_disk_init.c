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
typedef  int /*<<< orphan*/  _i32 ;
typedef  int /*<<< orphan*/  SlFsFileInfo_t ;
typedef  int /*<<< orphan*/  DRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_MODE_OPEN_CREATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_MODE_OPEN_WRITE ; 
 int /*<<< orphan*/  RES_ERROR ; 
 int /*<<< orphan*/  RES_OK ; 
 int SFLASH_BLOCK_COUNT ; 
 int /*<<< orphan*/  SFLASH_BLOCK_SIZE ; 
 int /*<<< orphan*/  SL_OS_WAIT_FOREVER ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/ * mem_Malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_block_name (int) ; 
 int /*<<< orphan*/  sflash_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sflash_block_cache ; 
 int /*<<< orphan*/  sflash_block_name ; 
 int sflash_cache_is_dirty ; 
 int sflash_init_done ; 
 int /*<<< orphan*/  sflash_prblock ; 
 int /*<<< orphan*/  sl_FsClose (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sl_FsGetInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sl_FsOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sl_FsWrite ; 
 int /*<<< orphan*/  sl_LockObjLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_LockObjUnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlan_LockObj ; 

DRESULT sflash_disk_init (void) {
    _i32 fileHandle;
    SlFsFileInfo_t FsFileInfo;

    if (!sflash_init_done) {
        // Allocate space for the block cache
        ASSERT ((sflash_block_cache = mem_Malloc(SFLASH_BLOCK_SIZE)) != NULL);
        sflash_init_done = true;
        sflash_prblock = UINT32_MAX;
        sflash_cache_is_dirty = false;

        // In order too speed up booting, check the last block, if exists, then
        // it means that the file system has been already created
        print_block_name (SFLASH_BLOCK_COUNT - 1);
        sl_LockObjLock (&wlan_LockObj, SL_OS_WAIT_FOREVER);
        if (!sl_FsGetInfo(sflash_block_name, 0, &FsFileInfo)) {
            sl_LockObjUnlock (&wlan_LockObj);
            return RES_OK;
        }
        sl_LockObjUnlock (&wlan_LockObj);

        // Proceed to format the memory
        for (int i = 0; i < SFLASH_BLOCK_COUNT; i++) {
            print_block_name (i);
            sl_LockObjLock (&wlan_LockObj, SL_OS_WAIT_FOREVER);
            // Create the block file if it doesn't exist
            if (sl_FsGetInfo(sflash_block_name, 0, &FsFileInfo) != 0) {
                if (!sl_FsOpen(sflash_block_name, FS_MODE_OPEN_CREATE(SFLASH_BLOCK_SIZE, 0), NULL, &fileHandle)) {
                    sl_FsClose(fileHandle, NULL, NULL, 0);
                    sl_LockObjUnlock (&wlan_LockObj);
                    memset(sflash_block_cache, 0xFF, SFLASH_BLOCK_SIZE);
                    if (!sflash_access(FS_MODE_OPEN_WRITE, sl_FsWrite)) {
                        return RES_ERROR;
                    }
                }
                else {
                    // Unexpected failure while creating the file
                    sl_LockObjUnlock (&wlan_LockObj);
                    return RES_ERROR;
                }
            }
            sl_LockObjUnlock (&wlan_LockObj);
        }
    }
    return RES_OK;
}