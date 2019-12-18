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
struct TYPE_4__ {int winsect; int* win; scalar_t__ wflag; } ;
typedef  TYPE_1__ FATFS ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int BS_55AA ; 
 int BS_FilSysType ; 
 int BS_FilSysType32 ; 
 int BS_JmpBoot ; 
 scalar_t__ FR_OK ; 
 int ld_word (int*) ; 
 int /*<<< orphan*/  mem_cmp (int*,char*,int) ; 
 scalar_t__ move_window (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BYTE check_fs (  /* 0:FAT, 1:exFAT, 2:Valid BS but not FAT, 3:Not a BS, 4:Disk error */
    FATFS* fs,          /* Filesystem object */
    DWORD sect          /* Sector# (lba) to load and check if it is an FAT-VBR or not */
)
{
    fs->wflag = 0; fs->winsect = 0xFFFFFFFF;        /* Invaidate window */
    if (move_window(fs, sect) != FR_OK) return 4;   /* Load boot record */

    if (ld_word(fs->win + BS_55AA) != 0xAA55) return 3; /* Check boot record signature (always here regardless of the sector size) */

#if FF_FS_EXFAT
    if (!mem_cmp(fs->win + BS_JmpBoot, "\xEB\x76\x90" "EXFAT   ", 11)) return 1;    /* Check if exFAT VBR */
#endif
    if (fs->win[BS_JmpBoot] == 0xE9 || fs->win[BS_JmpBoot] == 0xEB || fs->win[BS_JmpBoot] == 0xE8) {    /* Valid JumpBoot code? */
        if (!mem_cmp(fs->win + BS_FilSysType, "FAT", 3)) return 0;      /* Is it an FAT VBR? */
        if (!mem_cmp(fs->win + BS_FilSysType32, "FAT32", 5)) return 0;  /* Is it an FAT32 VBR? */
    }
    return 2;   /* Valid BS but not FAT */
}