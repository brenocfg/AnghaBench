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
typedef  int /*<<< orphan*/  lfs1_t ;
typedef  int lfs1_soff_t ;
struct TYPE_4__ {int pos; int size; } ;
typedef  TYPE_1__ lfs1_file_t ;

/* Variables and functions */
 int LFS1_ERR_INVAL ; 
 int LFS1_FILE_MAX ; 
 int LFS1_SEEK_CUR ; 
 int LFS1_SEEK_END ; 
 int LFS1_SEEK_SET ; 
 int lfs1_file_flush (int /*<<< orphan*/ *,TYPE_1__*) ; 

lfs1_soff_t lfs1_file_seek(lfs1_t *lfs1, lfs1_file_t *file,
        lfs1_soff_t off, int whence) {
    // write out everything beforehand, may be noop if rdonly
    int err = lfs1_file_flush(lfs1, file);
    if (err) {
        return err;
    }

    // find new pos
    lfs1_soff_t npos = file->pos;
    if (whence == LFS1_SEEK_SET) {
        npos = off;
    } else if (whence == LFS1_SEEK_CUR) {
        npos = file->pos + off;
    } else if (whence == LFS1_SEEK_END) {
        npos = file->size + off;
    }

    if (npos < 0 || npos > LFS1_FILE_MAX) {
        // file position out of range
        return LFS1_ERR_INVAL;
    }

    // update pos
    file->pos = npos;
    return npos;
}