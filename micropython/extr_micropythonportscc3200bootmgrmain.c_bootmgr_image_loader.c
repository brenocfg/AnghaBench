#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ActiveImg; scalar_t__ Status; int PrevImg; } ;
typedef  TYPE_1__ sBootInfo_t ;
typedef  unsigned char _u8 ;
typedef  int /*<<< orphan*/  _i32 ;

/* Variables and functions */
 int /*<<< orphan*/  FS_MODE_OPEN_WRITE ; 
 int IMG_ACT_FACTORY ; 
#define  IMG_ACT_UPDATE1 129 
#define  IMG_ACT_UPDATE2 128 
 scalar_t__ IMG_BOOT_INFO ; 
 scalar_t__ IMG_FACTORY ; 
 scalar_t__ IMG_STATUS_CHECK ; 
 scalar_t__ IMG_STATUS_READY ; 
 scalar_t__ IMG_UPDATE1 ; 
 scalar_t__ IMG_UPDATE2 ; 
 int /*<<< orphan*/  bootmgr_load_and_execute (unsigned char*) ; 
 int /*<<< orphan*/  bootmgr_verify (unsigned char*) ; 
 int /*<<< orphan*/  sl_FsClose (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_FsDel (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_FsOpen (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sl_FsWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  wait_for_safe_boot (TYPE_1__*) ; 

__attribute__((used)) static void bootmgr_image_loader(sBootInfo_t *psBootInfo) {
    _i32 fhandle;
    _u8 *image;

    // search for the active image
    switch (psBootInfo->ActiveImg) {
    case IMG_ACT_UPDATE1:
        image = (unsigned char *)IMG_UPDATE1;
        break;
    case IMG_ACT_UPDATE2:
        image = (unsigned char *)IMG_UPDATE2;
        break;
    default:
        image = (unsigned char *)IMG_FACTORY;
        break;
    }

    // do we have a new image that needs to be verified?
    if ((psBootInfo->ActiveImg != IMG_ACT_FACTORY) && (psBootInfo->Status == IMG_STATUS_CHECK)) {
        if (!bootmgr_verify(image)) {
            // verification failed, delete the broken file
            sl_FsDel(image, 0);
            // switch to the previous image
            psBootInfo->ActiveImg = psBootInfo->PrevImg;
            psBootInfo->PrevImg = IMG_ACT_FACTORY;
        }
        // in any case, change the status to "READY"
        psBootInfo->Status = IMG_STATUS_READY;
        // write the new boot info
        if (!sl_FsOpen((unsigned char *)IMG_BOOT_INFO, FS_MODE_OPEN_WRITE, NULL, &fhandle)) {
            sl_FsWrite(fhandle, 0, (unsigned char *)psBootInfo, sizeof(sBootInfo_t));
            // close the file
            sl_FsClose(fhandle, 0, 0, 0);
        }
    }

    // this one might modify the boot info hence it MUST be called after
    // bootmgr_verify! (so that the changes are not saved to flash)
    wait_for_safe_boot(psBootInfo);

    // select the active image again, since it might have changed
    switch (psBootInfo->ActiveImg) {
    case IMG_ACT_UPDATE1:
        image = (unsigned char *)IMG_UPDATE1;
        break;
    case IMG_ACT_UPDATE2:
        image = (unsigned char *)IMG_UPDATE2;
        break;
    default:
        image = (unsigned char *)IMG_FACTORY;
        break;
    }
    bootmgr_load_and_execute(image);
}