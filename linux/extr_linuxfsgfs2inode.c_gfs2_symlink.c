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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  GFS2_I (struct inode*) ; 
 int S_IFLNK ; 
 int S_IRWXUGO ; 
 int gfs2_create_inode (struct inode*,struct dentry*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int gfs2_max_stuffed_size (int /*<<< orphan*/ ) ; 
 unsigned int strlen (char const*) ; 

__attribute__((used)) static int gfs2_symlink(struct inode *dir, struct dentry *dentry,
			const char *symname)
{
	unsigned int size;

	size = strlen(symname);
	if (size >= gfs2_max_stuffed_size(GFS2_I(dir)))
		return -ENAMETOOLONG;

	return gfs2_create_inode(dir, dentry, NULL, S_IFLNK | S_IRWXUGO, 0, symname, size, 0);
}