#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char UINT ;
struct TYPE_10__ {int attr; int /*<<< orphan*/  sclust; TYPE_2__* fs; } ;
struct TYPE_12__ {int* fn; int dptr; TYPE_1__ obj; } ;
struct TYPE_11__ {scalar_t__ win; } ;
typedef  char TCHAR ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_2__ FATFS ;
typedef  TYPE_3__ DIR ;
typedef  int BYTE ;

/* Variables and functions */
 int AM_DIR ; 
 scalar_t__ FF_FS_RPATH ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_NO_PATH ; 
 scalar_t__ FR_OK ; 
 size_t NSFLAG ; 
 int NS_DOT ; 
 int NS_LAST ; 
 void* NS_NONAME ; 
 int SS (TYPE_2__*) ; 
 scalar_t__ create_name (TYPE_3__*,char const**) ; 
 scalar_t__ dir_find (TYPE_3__*) ; 
 scalar_t__ dir_sdi (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ld_clust (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static FRESULT follow_path (    /* FR_OK(0): successful, !=0: error code */
    DIR* dp,                    /* Directory object to return last directory and found object */
    const TCHAR* path           /* Full-path string to find a file or directory */
)
{
    FRESULT res;
    BYTE ns;
    FATFS *fs = dp->obj.fs;


#if FF_FS_RPATH != 0
    if (*path != '/' && *path != '\\') {    /* Without heading separator */
        dp->obj.sclust = fs->cdir;              /* Start from current directory */
    } else
#endif
    {                                       /* With heading separator */
        while (*path == '/' || *path == '\\') path++;   /* Strip heading separator */
        dp->obj.sclust = 0;                 /* Start from root directory */
    }
#if FF_FS_EXFAT
    dp->obj.n_frag = 0; /* Invalidate last fragment counter of the object */
#if FF_FS_RPATH != 0
    if (fs->fs_type == FS_EXFAT && dp->obj.sclust) {    /* exFAT: Retrieve the sub-directory's status */
        DIR dj;

        dp->obj.c_scl = fs->cdc_scl;
        dp->obj.c_size = fs->cdc_size;
        dp->obj.c_ofs = fs->cdc_ofs;
        res = load_obj_xdir(&dj, &dp->obj);
        if (res != FR_OK) return res;
        dp->obj.objsize = ld_dword(fs->dirbuf + XDIR_FileSize);
        dp->obj.stat = fs->dirbuf[XDIR_GenFlags] & 2;
    }
#endif
#endif

    if ((UINT)*path < ' ') {                /* Null path name is the origin directory itself */
        dp->fn[NSFLAG] = NS_NONAME;
        res = dir_sdi(dp, 0);

    } else {                                /* Follow path */
        for (;;) {
            res = create_name(dp, &path);   /* Get a segment name of the path */
            if (res != FR_OK) break;
            res = dir_find(dp);             /* Find an object with the segment name */
            ns = dp->fn[NSFLAG];
            if (res != FR_OK) {             /* Failed to find the object */
                if (res == FR_NO_FILE) {    /* Object is not found */
                    if (FF_FS_RPATH && (ns & NS_DOT)) { /* If dot entry is not exist, stay there */
                        if (!(ns & NS_LAST)) continue;  /* Continue to follow if not last segment */
                        dp->fn[NSFLAG] = NS_NONAME;
                        res = FR_OK;
                    } else {                            /* Could not find the object */
                        if (!(ns & NS_LAST)) res = FR_NO_PATH;  /* Adjust error code if not last segment */
                    }
                }
                break;
            }
            if (ns & NS_LAST) break;            /* Last segment matched. Function completed. */
            /* Get into the sub-directory */
            if (!(dp->obj.attr & AM_DIR)) {     /* It is not a sub-directory and cannot follow */
                res = FR_NO_PATH; break;
            }
#if FF_FS_EXFAT
            if (fs->fs_type == FS_EXFAT) {      /* Save containing directory information for next dir */
                dp->obj.c_scl = dp->obj.sclust;
                dp->obj.c_size = ((DWORD)dp->obj.objsize & 0xFFFFFF00) | dp->obj.stat;
                dp->obj.c_ofs = dp->blk_ofs;
                init_alloc_info(fs, &dp->obj);  /* Open next directory */
            } else
#endif
            {
                dp->obj.sclust = ld_clust(fs, fs->win + dp->dptr % SS(fs)); /* Open next directory */
            }
        }
    }

    return res;
}