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
typedef  int /*<<< orphan*/  lfs1_t ;
typedef  scalar_t__ lfs1_soff_t ;
typedef  int /*<<< orphan*/  lfs1_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  LFS1_SEEK_SET ; 
 scalar_t__ lfs1_file_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int lfs1_file_rewind(lfs1_t *lfs1, lfs1_file_t *file) {
    lfs1_soff_t res = lfs1_file_seek(lfs1, file, 0, LFS1_SEEK_SET);
    if (res < 0) {
        return res;
    }

    return 0;
}