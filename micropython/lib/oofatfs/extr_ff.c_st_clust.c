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
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_3__ {scalar_t__ fs_type; } ;
typedef  TYPE_1__ FATFS ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int DIR_FstClusHI ; 
 int DIR_FstClusLO ; 
 scalar_t__ FS_FAT32 ; 
 int /*<<< orphan*/  st_word (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void st_clust (
    FATFS* fs,  /* Pointer to the fs object */
    BYTE* dir,  /* Pointer to the key entry */
    DWORD cl    /* Value to be set */
)
{
    st_word(dir + DIR_FstClusLO, (WORD)cl);
    if (fs->fs_type == FS_FAT32) {
        st_word(dir + DIR_FstClusHI, (WORD)(cl >> 16));
    }
}