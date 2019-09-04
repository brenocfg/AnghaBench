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
struct disk {struct disk* name; int /*<<< orphan*/  st_svctm; int /*<<< orphan*/  st_avagsz; int /*<<< orphan*/  st_await; int /*<<< orphan*/  st_iotime; int /*<<< orphan*/  st_util; int /*<<< orphan*/  st_qops; int /*<<< orphan*/  st_ops; int /*<<< orphan*/  st_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  disks_added ; 
 int /*<<< orphan*/  freez (struct disk*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_is_obsolete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disk_free(struct disk *dm) {
    if (likely(dm->st_io))
        rrdset_is_obsolete(dm->st_io);
    if (likely(dm->st_ops))
        rrdset_is_obsolete(dm->st_ops);
    if (likely(dm->st_qops))
        rrdset_is_obsolete(dm->st_qops);
    if (likely(dm->st_util))
        rrdset_is_obsolete(dm->st_util);
    if (likely(dm->st_iotime))
        rrdset_is_obsolete(dm->st_iotime);
    if (likely(dm->st_await))
        rrdset_is_obsolete(dm->st_await);
    if (likely(dm->st_avagsz))
        rrdset_is_obsolete(dm->st_avagsz);
    if (likely(dm->st_svctm))
        rrdset_is_obsolete(dm->st_svctm);

    disks_added--;
    freez(dm->name);
    freez(dm);
}