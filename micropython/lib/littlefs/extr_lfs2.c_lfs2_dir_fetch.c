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
typedef  int /*<<< orphan*/  lfs2_mdir_t ;
typedef  int /*<<< orphan*/  lfs2_block_t ;

/* Variables and functions */
 scalar_t__ lfs2_dir_fetchmatch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lfs2_dir_fetch(lfs2_t *lfs2,
        lfs2_mdir_t *dir, const lfs2_block_t pair[2]) {
    // note, mask=-1, tag=0 can never match a tag since this
    // pattern has the invalid bit set
    return (int)lfs2_dir_fetchmatch(lfs2, dir, pair, -1, 0, NULL, NULL, NULL);
}