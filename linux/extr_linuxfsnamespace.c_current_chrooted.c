#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct path {int /*<<< orphan*/  dentry; TYPE_1__* mnt; } ;
struct TYPE_10__ {int /*<<< orphan*/  fs; TYPE_4__* nsproxy; } ;
struct TYPE_9__ {TYPE_3__* mnt_ns; } ;
struct TYPE_8__ {TYPE_2__* root; } ;
struct TYPE_6__ {int /*<<< orphan*/  mnt_root; } ;
struct TYPE_7__ {TYPE_1__ mnt; } ;

/* Variables and functions */
 TYPE_5__* current ; 
 scalar_t__ d_mountpoint (int /*<<< orphan*/ ) ; 
 scalar_t__ follow_down_one (struct path*) ; 
 int /*<<< orphan*/  get_fs_root (int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  path_equal (struct path*,struct path*) ; 
 int /*<<< orphan*/  path_get (struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 

bool current_chrooted(void)
{
	/* Does the current process have a non-standard root */
	struct path ns_root;
	struct path fs_root;
	bool chrooted;

	/* Find the namespace root */
	ns_root.mnt = &current->nsproxy->mnt_ns->root->mnt;
	ns_root.dentry = ns_root.mnt->mnt_root;
	path_get(&ns_root);
	while (d_mountpoint(ns_root.dentry) && follow_down_one(&ns_root))
		;

	get_fs_root(current->fs, &fs_root);

	chrooted = !path_equal(&fs_root, &ns_root);

	path_put(&fs_root);
	path_put(&ns_root);

	return chrooted;
}