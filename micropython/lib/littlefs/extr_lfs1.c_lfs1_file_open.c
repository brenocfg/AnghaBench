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
typedef  int /*<<< orphan*/  lfs1_file_t ;

/* Variables and functions */
 int lfs1_file_opencfg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 

int lfs1_file_open(lfs1_t *lfs1, lfs1_file_t *file,
        const char *path, int flags) {
    return lfs1_file_opencfg(lfs1, file, path, flags, NULL);
}