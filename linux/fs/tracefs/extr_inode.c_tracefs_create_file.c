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
typedef  int umode_t ;
struct inode {int i_mode; void* i_private; struct file_operations const* i_fop; } ;
struct file_operations {int dummy; } ;
struct dentry {TYPE_1__* d_parent; int /*<<< orphan*/  d_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  LOCKDOWN_TRACEFS ; 
 int S_IFMT ; 
 int S_IFREG ; 
 int /*<<< orphan*/  S_ISREG (int) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 struct dentry* end_creating (struct dentry*) ; 
 struct dentry* failed_creating (struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_create (int /*<<< orphan*/ ,struct dentry*) ; 
 scalar_t__ security_locked_down (int /*<<< orphan*/ ) ; 
 struct dentry* start_creating (char const*,struct dentry*) ; 
 struct file_operations const tracefs_file_operations ; 
 struct inode* tracefs_get_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct dentry *tracefs_create_file(const char *name, umode_t mode,
				   struct dentry *parent, void *data,
				   const struct file_operations *fops)
{
	struct dentry *dentry;
	struct inode *inode;

	if (security_locked_down(LOCKDOWN_TRACEFS))
		return NULL;

	if (!(mode & S_IFMT))
		mode |= S_IFREG;
	BUG_ON(!S_ISREG(mode));
	dentry = start_creating(name, parent);

	if (IS_ERR(dentry))
		return NULL;

	inode = tracefs_get_inode(dentry->d_sb);
	if (unlikely(!inode))
		return failed_creating(dentry);

	inode->i_mode = mode;
	inode->i_fop = fops ? fops : &tracefs_file_operations;
	inode->i_private = data;
	d_instantiate(dentry, inode);
	fsnotify_create(dentry->d_parent->d_inode, dentry);
	return end_creating(dentry);
}