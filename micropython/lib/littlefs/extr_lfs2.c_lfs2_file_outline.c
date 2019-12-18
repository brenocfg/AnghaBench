#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lfs2_t ;
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  pos; int /*<<< orphan*/  off; } ;
typedef  TYPE_1__ lfs2_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  LFS2_F_INLINE ; 
 int /*<<< orphan*/  lfs2_alloc_ack (int /*<<< orphan*/ *) ; 
 int lfs2_file_relocate (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int lfs2_file_outline(lfs2_t *lfs2, lfs2_file_t *file) {
    file->off = file->pos;
    lfs2_alloc_ack(lfs2);
    int err = lfs2_file_relocate(lfs2, file);
    if (err) {
        return err;
    }

    file->flags &= ~LFS2_F_INLINE;
    return 0;
}