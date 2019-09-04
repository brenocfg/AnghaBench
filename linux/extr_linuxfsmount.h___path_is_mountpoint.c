#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct path {int /*<<< orphan*/  dentry; int /*<<< orphan*/  mnt; } ;
struct TYPE_2__ {int mnt_flags; } ;
struct mount {TYPE_1__ mnt; } ;

/* Variables and functions */
 int MNT_SYNC_UMOUNT ; 
 struct mount* __lookup_mnt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline bool __path_is_mountpoint(const struct path *path)
{
	struct mount *m = __lookup_mnt(path->mnt, path->dentry);
	return m && likely(!(m->mnt.mnt_flags & MNT_SYNC_UMOUNT));
}