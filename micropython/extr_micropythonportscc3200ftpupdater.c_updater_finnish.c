#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sBootInfo_t ;
typedef  int _i32 ;
struct TYPE_4__ {int /*<<< orphan*/  Status; int /*<<< orphan*/  ActiveImg; int /*<<< orphan*/  PrevImg; } ;
struct TYPE_3__ {int fhandle; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FS_MODE_OPEN_WRITE ; 
 int /*<<< orphan*/  IMG_ACT_FACTORY ; 
 int /*<<< orphan*/  IMG_ACT_UPDATE1 ; 
 scalar_t__ IMG_BOOT_INFO ; 
 int /*<<< orphan*/  IMG_PREFIX ; 
 int /*<<< orphan*/  IMG_STATUS_CHECK ; 
 int /*<<< orphan*/  SL_OS_WAIT_FOREVER ; 
 TYPE_2__ sBootInfo ; 
 int /*<<< orphan*/  sl_FsClose (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sl_FsOpen (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int sl_FsWrite (int,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  sl_LockObjLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_LockObjUnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  updater_LockObj ; 
 TYPE_1__ updater_data ; 
 int /*<<< orphan*/  wlan_LockObj ; 

void updater_finnish (void) {
    _i32 fhandle;

    if (updater_data.fhandle > 0) {
        sl_LockObjLock (&wlan_LockObj, SL_OS_WAIT_FOREVER);
        // close the file being updated
        sl_FsClose(updater_data.fhandle, NULL, NULL, 0);
#ifdef WIPY
        // if we still have an image pending for verification, leave the boot info as it is
        if (!strncmp(IMG_PREFIX, updater_data.path, strlen(IMG_PREFIX)) && sBootInfo.Status != IMG_STATUS_CHECK) {
#else
        if (!strncmp(IMG_PREFIX, updater_data.path, strlen(IMG_PREFIX))) {
#endif
#ifdef DEBUG
            if (!sl_FsOpen((unsigned char *)IMG_BOOT_INFO, FS_MODE_OPEN_READ, NULL, &fhandle)) {

                ASSERT (sizeof(sBootInfo_t) == sl_FsRead(fhandle, 0, (unsigned char *)&sBootInfo, sizeof(sBootInfo_t)));
                sl_FsClose(fhandle, 0, 0, 0);
#endif
                // open the boot info file for writing
                ASSERT (sl_FsOpen((unsigned char *)IMG_BOOT_INFO, FS_MODE_OPEN_WRITE, NULL, &fhandle) == 0);
#ifdef DEBUG
            }
            else {
                // the boot info file doesn't exist yet
                _u32 BootInfoCreateFlag  = _FS_FILE_OPEN_FLAG_COMMIT | _FS_FILE_PUBLIC_WRITE | _FS_FILE_PUBLIC_READ;
                ASSERT (sl_FsOpen ((unsigned char *)IMG_BOOT_INFO, FS_MODE_OPEN_CREATE((2 * sizeof(sBootInfo_t)),
                                   BootInfoCreateFlag), NULL, &fhandle) == 0);
            }
#endif

            // save the new boot info
#ifdef WIPY
            sBootInfo.PrevImg = sBootInfo.ActiveImg;
            if (sBootInfo.ActiveImg == IMG_ACT_UPDATE1) {
                sBootInfo.ActiveImg = IMG_ACT_UPDATE2;
            } else {
                sBootInfo.ActiveImg = IMG_ACT_UPDATE1;
            }
// the launchxl doesn't have enough flash space for 2 user updates
#else
            sBootInfo.PrevImg = IMG_ACT_FACTORY;
            sBootInfo.ActiveImg = IMG_ACT_UPDATE1;
#endif
            sBootInfo.Status = IMG_STATUS_CHECK;
            ASSERT (sizeof(sBootInfo_t) == sl_FsWrite(fhandle, 0, (unsigned char *)&sBootInfo, sizeof(sBootInfo_t)));
            sl_FsClose(fhandle, 0, 0, 0);
        }
        sl_LockObjUnlock (&wlan_LockObj);
        updater_data.fhandle = -1;
    }
    sl_LockObjUnlock (&updater_LockObj);
}