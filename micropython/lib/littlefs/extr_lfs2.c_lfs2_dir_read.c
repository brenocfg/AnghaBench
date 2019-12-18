#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lfs2_info {int /*<<< orphan*/  name; void* type; } ;
typedef  int /*<<< orphan*/  lfs2_t ;
struct TYPE_6__ {scalar_t__ count; int /*<<< orphan*/  tail; int /*<<< orphan*/  split; } ;
struct TYPE_5__ {int pos; scalar_t__ id; TYPE_3__ m; } ;
typedef  TYPE_1__ lfs2_dir_t ;

/* Variables and functions */
 int LFS2_ERR_NOENT ; 
 int /*<<< orphan*/  LFS2_TRACE (char*,int,...) ; 
 void* LFS2_TYPE_DIR ; 
 int lfs2_dir_fetch (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int lfs2_dir_getinfo (int /*<<< orphan*/ *,TYPE_3__*,scalar_t__,struct lfs2_info*) ; 
 int /*<<< orphan*/  memset (struct lfs2_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int lfs2_dir_read(lfs2_t *lfs2, lfs2_dir_t *dir, struct lfs2_info *info) {
    LFS2_TRACE("lfs2_dir_read(%p, %p, %p)",
            (void*)lfs2, (void*)dir, (void*)info);
    memset(info, 0, sizeof(*info));

    // special offset for '.' and '..'
    if (dir->pos == 0) {
        info->type = LFS2_TYPE_DIR;
        strcpy(info->name, ".");
        dir->pos += 1;
        LFS2_TRACE("lfs2_dir_read -> %d", true);
        return true;
    } else if (dir->pos == 1) {
        info->type = LFS2_TYPE_DIR;
        strcpy(info->name, "..");
        dir->pos += 1;
        LFS2_TRACE("lfs2_dir_read -> %d", true);
        return true;
    }

    while (true) {
        if (dir->id == dir->m.count) {
            if (!dir->m.split) {
                LFS2_TRACE("lfs2_dir_read -> %d", false);
                return false;
            }

            int err = lfs2_dir_fetch(lfs2, &dir->m, dir->m.tail);
            if (err) {
                LFS2_TRACE("lfs2_dir_read -> %d", err);
                return err;
            }

            dir->id = 0;
        }

        int err = lfs2_dir_getinfo(lfs2, &dir->m, dir->id, info);
        if (err && err != LFS2_ERR_NOENT) {
            LFS2_TRACE("lfs2_dir_read -> %d", err);
            return err;
        }

        dir->id += 1;
        if (err != LFS2_ERR_NOENT) {
            break;
        }
    }

    dir->pos += 1;
    LFS2_TRACE("lfs2_dir_read -> %d", true);
    return true;
}