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
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  hash; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  d_sb; } ;
struct TYPE_2__ {struct inode* dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct dir_context {int dummy; } ;
struct dentry {int i_mode; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  d_sb; } ;
struct ctl_table_header {int dummy; } ;
struct ctl_table {int /*<<< orphan*/  procname; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAIT_QUEUE_HEAD_ONSTACK (int /*<<< orphan*/ ) ; 
 unsigned int DT_UNKNOWN ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 struct inode* d_alloc_parallel (struct inode*,struct qstr*,int /*<<< orphan*/ *) ; 
 scalar_t__ d_in_lookup (struct inode*) ; 
 struct inode* d_inode (struct inode*) ; 
 struct inode* d_lookup (struct inode*,struct qstr*) ; 
 int /*<<< orphan*/  d_lookup_done (struct inode*) ; 
 int /*<<< orphan*/  d_set_d_op (struct inode*,int /*<<< orphan*/ *) ; 
 struct inode* d_splice_alias (struct inode*,struct inode*) ; 
 int dir_emit (struct dir_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dput (struct inode*) ; 
 int /*<<< orphan*/  full_name_hash (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_sys_dentry_operations ; 
 struct inode* proc_sys_make_inode (int /*<<< orphan*/ ,struct ctl_table_header*,struct ctl_table*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (struct inode*) ; 
 int /*<<< orphan*/  wq ; 

__attribute__((used)) static bool proc_sys_fill_cache(struct file *file,
				struct dir_context *ctx,
				struct ctl_table_header *head,
				struct ctl_table *table)
{
	struct dentry *child, *dir = file->f_path.dentry;
	struct inode *inode;
	struct qstr qname;
	ino_t ino = 0;
	unsigned type = DT_UNKNOWN;

	qname.name = table->procname;
	qname.len  = strlen(table->procname);
	qname.hash = full_name_hash(dir, qname.name, qname.len);

	child = d_lookup(dir, &qname);
	if (!child) {
		DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);
		child = d_alloc_parallel(dir, &qname, &wq);
		if (IS_ERR(child))
			return false;
		if (d_in_lookup(child)) {
			struct dentry *res;
			inode = proc_sys_make_inode(dir->d_sb, head, table);
			if (IS_ERR(inode)) {
				d_lookup_done(child);
				dput(child);
				return false;
			}
			d_set_d_op(child, &proc_sys_dentry_operations);
			res = d_splice_alias(inode, child);
			d_lookup_done(child);
			if (unlikely(res)) {
				if (IS_ERR(res)) {
					dput(child);
					return false;
				}
				dput(child);
				child = res;
			}
		}
	}
	inode = d_inode(child);
	ino  = inode->i_ino;
	type = inode->i_mode >> 12;
	dput(child);
	return dir_emit(ctx, qname.name, qname.len, ino, type);
}