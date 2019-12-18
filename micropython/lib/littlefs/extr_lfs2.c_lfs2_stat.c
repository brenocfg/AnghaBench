#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lfs2_info {int dummy; } ;
typedef  int /*<<< orphan*/  lfs2_t ;
typedef  int lfs2_stag_t ;
typedef  int /*<<< orphan*/  lfs2_mdir_t ;

/* Variables and functions */
 int /*<<< orphan*/  LFS2_TRACE (char*,int,...) ; 
 int lfs2_dir_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int lfs2_dir_getinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct lfs2_info*) ; 
 int /*<<< orphan*/  lfs2_tag_id (int) ; 

int lfs2_stat(lfs2_t *lfs2, const char *path, struct lfs2_info *info) {
    LFS2_TRACE("lfs2_stat(%p, \"%s\", %p)", (void*)lfs2, path, (void*)info);
    lfs2_mdir_t cwd;
    lfs2_stag_t tag = lfs2_dir_find(lfs2, &cwd, &path, NULL);
    if (tag < 0) {
        LFS2_TRACE("lfs2_stat -> %d", tag);
        return (int)tag;
    }

    int err = lfs2_dir_getinfo(lfs2, &cwd, lfs2_tag_id(tag), info);
    LFS2_TRACE("lfs2_stat -> %d", err);
    return err;
}