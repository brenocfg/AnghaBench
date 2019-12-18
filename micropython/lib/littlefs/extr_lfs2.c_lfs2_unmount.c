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

/* Variables and functions */
 int /*<<< orphan*/  LFS2_TRACE (char*,int) ; 
 int lfs2_deinit (int /*<<< orphan*/ *) ; 

int lfs2_unmount(lfs2_t *lfs2) {
    LFS2_TRACE("lfs2_unmount(%p)", (void*)lfs2);
    int err = lfs2_deinit(lfs2);
    LFS2_TRACE("lfs2_unmount -> %d", err);
    return err;
}