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
typedef  int /*<<< orphan*/  lfs2_tag_t ;
typedef  int /*<<< orphan*/  lfs2_size_t ;

/* Variables and functions */
 scalar_t__ lfs2_tag_dsize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lfs2_dir_commit_size(void *p, lfs2_tag_t tag, const void *buffer) {
    lfs2_size_t *size = p;
    (void)buffer;

    *size += lfs2_tag_dsize(tag);
    return 0;
}