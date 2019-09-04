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
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int ecryptfs_do_unlink (struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecryptfs_unlink(struct inode *dir, struct dentry *dentry)
{
	return ecryptfs_do_unlink(dir, dentry, d_inode(dentry));
}