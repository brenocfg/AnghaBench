#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lfs1_t ;
struct TYPE_15__ {int flags; int /*<<< orphan*/  size; int /*<<< orphan*/  head; int /*<<< orphan*/  poff; int /*<<< orphan*/  pair; } ;
typedef  TYPE_3__ lfs1_file_t ;
struct TYPE_13__ {int /*<<< orphan*/  size; int /*<<< orphan*/  head; } ;
struct TYPE_14__ {TYPE_1__ file; } ;
struct TYPE_18__ {scalar_t__ type; TYPE_2__ u; } ;
struct TYPE_16__ {TYPE_8__ d; int /*<<< orphan*/  off; } ;
typedef  TYPE_4__ lfs1_entry_t ;
struct TYPE_17__ {int /*<<< orphan*/ * pair; } ;
typedef  TYPE_5__ lfs1_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  LFS1_ASSERT (int) ; 
 int LFS1_F_DIRTY ; 
 int LFS1_F_ERRED ; 
 scalar_t__ LFS1_TYPE_REG ; 
 int lfs1_bd_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*,int) ; 
 int lfs1_dir_fetch (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int lfs1_dir_update (int /*<<< orphan*/ *,TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lfs1_entry_fromle32 (TYPE_8__*) ; 
 int lfs1_file_flush (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  lfs1_pairisnull (int /*<<< orphan*/ ) ; 

int lfs1_file_sync(lfs1_t *lfs1, lfs1_file_t *file) {
    int err = lfs1_file_flush(lfs1, file);
    if (err) {
        return err;
    }

    if ((file->flags & LFS1_F_DIRTY) &&
            !(file->flags & LFS1_F_ERRED) &&
            !lfs1_pairisnull(file->pair)) {
        // update dir entry
        lfs1_dir_t cwd;
        err = lfs1_dir_fetch(lfs1, &cwd, file->pair);
        if (err) {
            return err;
        }

        lfs1_entry_t entry = {.off = file->poff};
        err = lfs1_bd_read(lfs1, cwd.pair[0], entry.off,
                &entry.d, sizeof(entry.d));
        lfs1_entry_fromle32(&entry.d);
        if (err) {
            return err;
        }

        LFS1_ASSERT(entry.d.type == LFS1_TYPE_REG);
        entry.d.u.file.head = file->head;
        entry.d.u.file.size = file->size;

        err = lfs1_dir_update(lfs1, &cwd, &entry, NULL);
        if (err) {
            return err;
        }

        file->flags &= ~LFS1_F_DIRTY;
    }

    return 0;
}