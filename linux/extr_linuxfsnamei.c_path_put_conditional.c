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
struct path {scalar_t__ mnt; int /*<<< orphan*/  dentry; } ;
struct TYPE_2__ {scalar_t__ mnt; } ;
struct nameidata {TYPE_1__ path; } ;

/* Variables and functions */
 int /*<<< orphan*/  dput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mntput (scalar_t__) ; 

__attribute__((used)) static void path_put_conditional(struct path *path, struct nameidata *nd)
{
	dput(path->dentry);
	if (path->mnt != nd->path.mnt)
		mntput(path->mnt);
}