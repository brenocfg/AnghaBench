#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct lfs2_mattr {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/ * root; } ;
typedef  TYPE_1__ lfs2_t ;
struct TYPE_12__ {int split; int /*<<< orphan*/ * pair; int /*<<< orphan*/ * tail; } ;
typedef  TYPE_2__ lfs2_mdir_t ;

/* Variables and functions */
 int lfs2_dir_alloc (TYPE_1__*,TYPE_2__*) ; 
 int lfs2_dir_compact (TYPE_1__*,TYPE_2__*,struct lfs2_mattr const*,int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lfs2_pair_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lfs2_dir_split(lfs2_t *lfs2,
        lfs2_mdir_t *dir, const struct lfs2_mattr *attrs, int attrcount,
        lfs2_mdir_t *source, uint16_t split, uint16_t end) {
    // create tail directory
    lfs2_mdir_t tail;
    int err = lfs2_dir_alloc(lfs2, &tail);
    if (err) {
        return err;
    }

    tail.split = dir->split;
    tail.tail[0] = dir->tail[0];
    tail.tail[1] = dir->tail[1];

    err = lfs2_dir_compact(lfs2, &tail, attrs, attrcount, source, split, end);
    if (err) {
        return err;
    }

    dir->tail[0] = tail.pair[0];
    dir->tail[1] = tail.pair[1];
    dir->split = true;

    // update root if needed
    if (lfs2_pair_cmp(dir->pair, lfs2->root) == 0 && split == 0) {
        lfs2->root[0] = tail.pair[0];
        lfs2->root[1] = tail.pair[1];
    }

    return 0;
}