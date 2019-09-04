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
struct TYPE_4__ {int winsect; int /*<<< orphan*/  win; int /*<<< orphan*/  drv; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FATFS ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ FR_DISK_ERR ; 
 scalar_t__ FR_OK ; 
 scalar_t__ RES_OK ; 
 scalar_t__ disk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ sync_window (TYPE_1__*) ; 

__attribute__((used)) static FRESULT move_window (    /* Returns FR_OK or FR_DISK_ERR */
    FATFS* fs,          /* Filesystem object */
    DWORD sector        /* Sector number to make appearance in the fs->win[] */
)
{
    FRESULT res = FR_OK;


    if (sector != fs->winsect) {    /* Window offset changed? */
#if !FF_FS_READONLY
        res = sync_window(fs);      /* Write-back changes */
#endif
        if (res == FR_OK) {         /* Fill sector window with new data */
            if (disk_read(fs->drv, fs->win, sector, 1) != RES_OK) {
                sector = 0xFFFFFFFF;    /* Invalidate window if read data is not valid */
                res = FR_DISK_ERR;
            }
            fs->winsect = sector;
        }
    }
    return res;
}