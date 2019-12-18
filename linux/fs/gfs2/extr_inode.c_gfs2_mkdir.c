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
typedef  int umode_t ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_I (struct inode*) ; 
 int S_IFDIR ; 
 int gfs2_create_inode (struct inode*,struct dentry*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int gfs2_max_stuffed_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfs2_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	unsigned dsize = gfs2_max_stuffed_size(GFS2_I(dir));
	return gfs2_create_inode(dir, dentry, NULL, S_IFDIR | mode, 0, NULL, dsize, 0);
}