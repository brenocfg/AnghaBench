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
struct super_block {scalar_t__ s_magic; scalar_t__ s_root; } ;
struct path {TYPE_1__* mnt; } ;
struct TYPE_2__ {scalar_t__ mnt_root; struct super_block* mnt_sb; } ;

/* Variables and functions */
 scalar_t__ DEVPTS_SUPER_MAGIC ; 
 int ENODEV ; 
 int path_pts (struct path*) ; 

__attribute__((used)) static int devpts_ptmx_path(struct path *path)
{
	struct super_block *sb;
	int err;

	/* Is a devpts filesystem at "pts" in the same directory? */
	err = path_pts(path);
	if (err)
		return err;

	/* Is the path the root of a devpts filesystem? */
	sb = path->mnt->mnt_sb;
	if ((sb->s_magic != DEVPTS_SUPER_MAGIC) ||
	    (path->mnt->mnt_root != sb->s_root))
		return -ENODEV;

	return 0;
}