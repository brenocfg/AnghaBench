#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint ;
struct TYPE_7__ {scalar_t__ str; struct TYPE_7__* next; } ;
typedef  TYPE_1__ mp_vfs_mount_t ;
typedef  scalar_t__ ftp_result_t ;
struct TYPE_9__ {int volcount; int /*<<< orphan*/  dp; scalar_t__ listroot; } ;
struct TYPE_8__ {char* fname; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_2__ FILINFO ;

/* Variables and functions */
 scalar_t__ E_FTP_RESULT_CONTINUE ; 
 scalar_t__ E_FTP_RESULT_OK ; 
 scalar_t__ FR_OK ; 
 TYPE_1__* MP_STATE_VM (int /*<<< orphan*/ ) ; 
 scalar_t__ f_readdir (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ftp_close_files () ; 
 TYPE_4__ ftp_data ; 
 int ftp_print_eplf_drive (char*,int,scalar_t__) ; 
 int ftp_print_eplf_item (char*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  vfs_mount_table ; 

__attribute__((used)) static ftp_result_t ftp_list_dir (char *list, uint32_t maxlistsize, uint32_t *listsize) {
    uint next = 0;
    uint listcount = 0;
    FRESULT res;
    ftp_result_t result = E_FTP_RESULT_CONTINUE;
    FILINFO fno;
#if _USE_LFN
    // read up to 2 directory items
    while (listcount < 2) {
#else
    // read up to 4 directory items
    while (listcount < 4) {
#endif
        if (ftp_data.listroot) {
            // root directory "hack"
            mp_vfs_mount_t *vfs = MP_STATE_VM(vfs_mount_table);
            int i = ftp_data.volcount;
            while (vfs != NULL && i != 0) {
                vfs = vfs->next;
                i -= 1;
            }
            if (vfs == NULL) {
                if (!next) {
                    // no volume found this time, we are done
                    ftp_data.volcount = 0;
                }
                break;
            } else {
                next += ftp_print_eplf_drive((list + next), (maxlistsize - next), vfs->str + 1);
            }
            ftp_data.volcount++;
        } else {
            // a "normal" directory
            res = f_readdir(&ftp_data.dp, &fno);                                                       /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) {
                result = E_FTP_RESULT_OK;
                break;                                                                                 /* Break on error or end of dp */
            }
            if (fno.fname[0] == '.' && fno.fname[1] == 0) continue;                                    /* Ignore . entry */
            if (fno.fname[0] == '.' && fno.fname[1] == '.' && fno.fname[2] == 0) continue;             /* Ignore .. entry */

            // add the entry to the list
            next += ftp_print_eplf_item((list + next), (maxlistsize - next), &fno);
        }
        listcount++;
    }
    if (result == E_FTP_RESULT_OK) {
        ftp_close_files();
    }
    *listsize = next;
    return result;
}