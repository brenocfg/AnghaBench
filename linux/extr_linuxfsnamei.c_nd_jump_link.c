#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct path {TYPE_1__* dentry; } ;
struct nameidata {int /*<<< orphan*/  flags; struct path path; int /*<<< orphan*/  inode; } ;
struct TYPE_4__ {struct nameidata* nameidata; } ;
struct TYPE_3__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOOKUP_JUMPED ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  path_put (struct path*) ; 

void nd_jump_link(struct path *path)
{
	struct nameidata *nd = current->nameidata;
	path_put(&nd->path);

	nd->path = *path;
	nd->inode = nd->path.dentry->d_inode;
	nd->flags |= LOOKUP_JUMPED;
}