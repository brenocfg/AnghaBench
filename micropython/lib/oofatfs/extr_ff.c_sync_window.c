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
struct TYPE_3__ {scalar_t__ winsect; scalar_t__ fatbase; scalar_t__ fsize; int n_fats; int /*<<< orphan*/  win; int /*<<< orphan*/  drv; scalar_t__ wflag; } ;
typedef  int /*<<< orphan*/  FRESULT ;
typedef  TYPE_1__ FATFS ;

/* Variables and functions */
 int /*<<< orphan*/  FR_DISK_ERR ; 
 int /*<<< orphan*/  FR_OK ; 
 scalar_t__ RES_OK ; 
 scalar_t__ disk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static FRESULT sync_window (    /* Returns FR_OK or FR_DISK_ERR */
    FATFS* fs           /* Filesystem object */
)
{
    FRESULT res = FR_OK;


    if (fs->wflag) {    /* Is the disk access window dirty */
        if (disk_write(fs->drv, fs->win, fs->winsect, 1) == RES_OK) {   /* Write back the window */
            fs->wflag = 0;  /* Clear window dirty flag */
            if (fs->winsect - fs->fatbase < fs->fsize) {    /* Is it in the 1st FAT? */
                if (fs->n_fats == 2) disk_write(fs->drv, fs->win, fs->winsect + fs->fsize, 1); /* Reflect it to 2nd FAT if needed */
            }
        } else {
            res = FR_DISK_ERR;
        }
    }
    return res;
}