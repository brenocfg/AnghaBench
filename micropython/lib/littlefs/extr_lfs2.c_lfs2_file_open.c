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
struct lfs2_file_config {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  lfs2_t ;
typedef  int /*<<< orphan*/  lfs2_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  LFS2_TRACE (char*,int,...) ; 
 int lfs2_file_opencfg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,struct lfs2_file_config const*) ; 

int lfs2_file_open(lfs2_t *lfs2, lfs2_file_t *file,
        const char *path, int flags) {
    LFS2_TRACE("lfs2_file_open(%p, %p, \"%s\", %x)",
            (void*)lfs2, (void*)file, path, flags);
    static const struct lfs2_file_config defaults = {0};
    int err = lfs2_file_opencfg(lfs2, file, path, flags, &defaults);
    LFS2_TRACE("lfs2_file_open -> %d", err);
    return err;
}