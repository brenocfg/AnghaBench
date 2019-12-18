#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ id; int /*<<< orphan*/  drv; scalar_t__ fs_type; } ;
struct TYPE_7__ {scalar_t__ id; TYPE_2__* fs; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FFOBJID ;
typedef  TYPE_2__ FATFS ;
typedef  int DSTATUS ;

/* Variables and functions */
 scalar_t__ FR_INVALID_OBJECT ; 
 scalar_t__ FR_OK ; 
 scalar_t__ FR_TIMEOUT ; 
 int /*<<< orphan*/  IOCTL_STATUS ; 
 scalar_t__ RES_OK ; 
 int STA_NOINIT ; 
 scalar_t__ disk_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ lock_fs (TYPE_2__*) ; 
 int /*<<< orphan*/  unlock_fs (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static FRESULT validate (   /* Returns FR_OK or FR_INVALID_OBJECT */
    FFOBJID* obj,           /* Pointer to the FFOBJID, the 1st member in the FIL/DIR object, to check validity */
    FATFS** rfs             /* Pointer to pointer to the owner filesystem object to return */
)
{
    FRESULT res = FR_INVALID_OBJECT;
    DSTATUS stat;


    if (obj && obj->fs && obj->fs->fs_type && obj->id == obj->fs->id) { /* Test if the object is valid */
#if FF_FS_REENTRANT
        if (lock_fs(obj->fs)) { /* Obtain the filesystem object */
            if (disk_ioctl(obj->fs->drv, IOCTL_STATUS, &stat) == RES_OK && !(stat & STA_NOINIT)) { /* Test if the phsical drive is kept initialized */
                res = FR_OK;
            } else {
                unlock_fs(obj->fs, FR_OK);
            }
        } else {
            res = FR_TIMEOUT;
        }
#else
        if (disk_ioctl(obj->fs->drv, IOCTL_STATUS, &stat) == RES_OK && !(stat & STA_NOINIT)) { /* Test if the phsical drive is kept initialized */
            res = FR_OK;
        }
#endif
    }
    *rfs = (res == FR_OK) ? obj->fs : 0;    /* Corresponding filesystem object */
    return res;
}