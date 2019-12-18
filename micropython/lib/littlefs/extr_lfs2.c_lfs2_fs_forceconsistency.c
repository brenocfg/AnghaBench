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
 int lfs2_fs_demove (int /*<<< orphan*/ *) ; 
 int lfs2_fs_deorphan (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lfs2_fs_forceconsistency(lfs2_t *lfs2) {
    int err = lfs2_fs_demove(lfs2);
    if (err) {
        return err;
    }

    err = lfs2_fs_deorphan(lfs2);
    if (err) {
        return err;
    }

    return 0;
}