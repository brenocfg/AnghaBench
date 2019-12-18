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
typedef  int /*<<< orphan*/  _u8 ;
typedef  int /*<<< orphan*/  _i32 ;
struct TYPE_3__ {scalar_t__ FileLen; } ;
typedef  TYPE_1__ SlFsFileInfo_t ;

/* Variables and functions */
 scalar_t__ APP_IMG_SRAM_OFFSET ; 
 int /*<<< orphan*/  FS_MODE_OPEN_READ ; 
 int /*<<< orphan*/  SL_STOP_TIMEOUT ; 
 int /*<<< orphan*/  bootmgr_run_app (scalar_t__) ; 
 int /*<<< orphan*/  sl_FsClose (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_FsGetInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sl_FsOpen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sl_FsRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  sl_Stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bootmgr_load_and_execute (_u8 *image) {
    SlFsFileInfo_t pFsFileInfo;
    _i32 fhandle;
    // open the application binary
    if (!sl_FsOpen(image, FS_MODE_OPEN_READ, NULL, &fhandle)) {
        // get the file size
        if (!sl_FsGetInfo(image, 0, &pFsFileInfo)) {
            // read the application into SRAM
            if (pFsFileInfo.FileLen == sl_FsRead(fhandle, 0, (unsigned char *)APP_IMG_SRAM_OFFSET, pFsFileInfo.FileLen)) {
                // close the file
                sl_FsClose(fhandle, 0, 0, 0);
                // stop the network services
                sl_Stop(SL_STOP_TIMEOUT);
                // execute the application
                bootmgr_run_app(APP_IMG_SRAM_OFFSET);
            }
        }
    }
}