#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* dentry; TYPE_2__* mnt; } ;
struct nameidata {TYPE_3__ path; int /*<<< orphan*/  inode; int /*<<< orphan*/  root; } ;
struct TYPE_8__ {TYPE_1__* mnt_root; } ;
struct TYPE_7__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  follow_mount (TYPE_3__*) ; 
 int /*<<< orphan*/  follow_up (TYPE_3__*) ; 
 scalar_t__ path_equal (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int path_parent_directory (TYPE_3__*) ; 

__attribute__((used)) static int follow_dotdot(struct nameidata *nd)
{
	while(1) {
		if (path_equal(&nd->path, &nd->root))
			break;
		if (nd->path.dentry != nd->path.mnt->mnt_root) {
			int ret = path_parent_directory(&nd->path);
			if (ret)
				return ret;
			break;
		}
		if (!follow_up(&nd->path))
			break;
	}
	follow_mount(&nd->path);
	nd->inode = nd->path.dentry->d_inode;
	return 0;
}