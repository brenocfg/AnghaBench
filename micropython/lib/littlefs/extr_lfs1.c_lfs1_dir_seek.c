#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lfs1_t ;
typedef  int lfs1_off_t ;
struct TYPE_6__ {int size; int /*<<< orphan*/  tail; } ;
struct TYPE_7__ {int pos; int off; TYPE_1__ d; } ;
typedef  TYPE_2__ lfs1_dir_t ;

/* Variables and functions */
 int LFS1_ERR_INVAL ; 
 int lfs1_dir_fetch (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int lfs1_dir_rewind (int /*<<< orphan*/ *,TYPE_2__*) ; 

int lfs1_dir_seek(lfs1_t *lfs1, lfs1_dir_t *dir, lfs1_off_t off) {
    // simply walk from head dir
    int err = lfs1_dir_rewind(lfs1, dir);
    if (err) {
        return err;
    }
    dir->pos = off;

    while (off > (0x7fffffff & dir->d.size)) {
        off -= 0x7fffffff & dir->d.size;
        if (!(0x80000000 & dir->d.size)) {
            return LFS1_ERR_INVAL;
        }

        err = lfs1_dir_fetch(lfs1, dir, dir->d.tail);
        if (err) {
            return err;
        }
    }

    dir->off = off;
    return 0;
}