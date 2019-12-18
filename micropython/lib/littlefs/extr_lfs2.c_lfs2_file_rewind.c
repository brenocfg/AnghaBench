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
typedef  int /*<<< orphan*/  lfs2_t ;
typedef  scalar_t__ lfs2_soff_t ;
typedef  int /*<<< orphan*/  lfs2_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  LFS2_SEEK_SET ; 
 int /*<<< orphan*/  LFS2_TRACE (char*,void*,...) ; 
 scalar_t__ lfs2_file_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int lfs2_file_rewind(lfs2_t *lfs2, lfs2_file_t *file) {
    LFS2_TRACE("lfs2_file_rewind(%p, %p)", (void*)lfs2, (void*)file);
    lfs2_soff_t res = lfs2_file_seek(lfs2, file, 0, LFS2_SEEK_SET);
    if (res < 0) {
        LFS2_TRACE("lfs2_file_rewind -> %d", res);
        return (int)res;
    }

    LFS2_TRACE("lfs2_file_rewind -> %d", 0);
    return 0;
}