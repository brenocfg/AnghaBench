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
typedef  scalar_t__ uint32_t ;
struct jffs2_inode_info {int /*<<< orphan*/  sem; struct jffs2_full_dirent* dents; } ;
struct jffs2_full_dirent {unsigned int nhash; scalar_t__ version; scalar_t__ ino; int /*<<< orphan*/  name; struct jffs2_full_dirent* next; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 struct jffs2_inode_info* JFFS2_INODE_INFO (struct inode*) ; 
 scalar_t__ JFFS2_MAX_NAME_LEN ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 unsigned int full_name_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  jffs2_dbg (int,char*) ; 
 struct inode* jffs2_iget (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct dentry *jffs2_lookup(struct inode *dir_i, struct dentry *target,
				   unsigned int flags)
{
	struct jffs2_inode_info *dir_f;
	struct jffs2_full_dirent *fd = NULL, *fd_list;
	uint32_t ino = 0;
	struct inode *inode = NULL;
	unsigned int nhash;

	jffs2_dbg(1, "jffs2_lookup()\n");

	if (target->d_name.len > JFFS2_MAX_NAME_LEN)
		return ERR_PTR(-ENAMETOOLONG);

	dir_f = JFFS2_INODE_INFO(dir_i);

	/* The 'nhash' on the fd_list is not the same as the dentry hash */
	nhash = full_name_hash(NULL, target->d_name.name, target->d_name.len);

	mutex_lock(&dir_f->sem);

	/* NB: The 2.2 backport will need to explicitly check for '.' and '..' here */
	for (fd_list = dir_f->dents; fd_list && fd_list->nhash <= nhash; fd_list = fd_list->next) {
		if (fd_list->nhash == nhash &&
		    (!fd || fd_list->version > fd->version) &&
		    strlen(fd_list->name) == target->d_name.len &&
		    !strncmp(fd_list->name, target->d_name.name, target->d_name.len)) {
			fd = fd_list;
		}
	}
	if (fd)
		ino = fd->ino;
	mutex_unlock(&dir_f->sem);
	if (ino) {
		inode = jffs2_iget(dir_i->i_sb, ino);
		if (IS_ERR(inode))
			pr_warn("iget() failed for ino #%u\n", ino);
	}

	return d_splice_alias(inode, target);
}