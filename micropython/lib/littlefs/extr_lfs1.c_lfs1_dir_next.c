#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lfs1_t ;
struct TYPE_9__ {int off; int /*<<< orphan*/  d; } ;
typedef  TYPE_2__ lfs1_entry_t ;
struct TYPE_8__ {int size; int /*<<< orphan*/  tail; } ;
struct TYPE_10__ {int off; int pos; int /*<<< orphan*/ * pair; TYPE_1__ d; } ;
typedef  TYPE_3__ lfs1_dir_t ;

/* Variables and functions */
 int LFS1_ERR_NOENT ; 
 int lfs1_bd_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int lfs1_dir_fetch (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lfs1_entry_fromle32 (int /*<<< orphan*/ *) ; 
 scalar_t__ lfs1_entry_size (TYPE_2__*) ; 

__attribute__((used)) static int lfs1_dir_next(lfs1_t *lfs1, lfs1_dir_t *dir, lfs1_entry_t *entry) {
    while (dir->off + sizeof(entry->d) > (0x7fffffff & dir->d.size)-4) {
        if (!(0x80000000 & dir->d.size)) {
            entry->off = dir->off;
            return LFS1_ERR_NOENT;
        }

        int err = lfs1_dir_fetch(lfs1, dir, dir->d.tail);
        if (err) {
            return err;
        }

        dir->off = sizeof(dir->d);
        dir->pos += sizeof(dir->d) + 4;
    }

    int err = lfs1_bd_read(lfs1, dir->pair[0], dir->off,
            &entry->d, sizeof(entry->d));
    lfs1_entry_fromle32(&entry->d);
    if (err) {
        return err;
    }

    entry->off = dir->off;
    dir->off += lfs1_entry_size(entry);
    dir->pos += lfs1_entry_size(entry);
    return 0;
}