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
 struct dentry* __gfs2_lookup (struct inode*,struct dentry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *gfs2_lookup(struct inode *dir, struct dentry *dentry,
				  unsigned flags)
{
	return __gfs2_lookup(dir, dentry, NULL);
}