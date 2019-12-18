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
struct task_struct {int dummy; } ;
struct qstr {int dummy; } ;
struct inode {int i_ino; int i_mode; } ;
struct TYPE_2__ {struct dentry* dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct dir_context {int dummy; } ;
struct dentry {int dummy; } ;
typedef  struct dentry* (* instantiate_t ) (struct dentry*,struct task_struct*,void const*) ;
typedef  int ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAIT_QUEUE_HEAD_ONSTACK (int /*<<< orphan*/ ) ; 
 unsigned int DT_UNKNOWN ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 struct qstr QSTR_INIT (char const*,unsigned int) ; 
 struct dentry* d_alloc_parallel (struct dentry*,struct qstr*,int /*<<< orphan*/ *) ; 
 struct dentry* d_hash_and_lookup (struct dentry*,struct qstr*) ; 
 scalar_t__ d_in_lookup (struct dentry*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_lookup_done (struct dentry*) ; 
 int dir_emit (struct dir_context*,char const*,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 scalar_t__ unlikely (struct dentry*) ; 
 int /*<<< orphan*/  wq ; 

bool proc_fill_cache(struct file *file, struct dir_context *ctx,
	const char *name, unsigned int len,
	instantiate_t instantiate, struct task_struct *task, const void *ptr)
{
	struct dentry *child, *dir = file->f_path.dentry;
	struct qstr qname = QSTR_INIT(name, len);
	struct inode *inode;
	unsigned type = DT_UNKNOWN;
	ino_t ino = 1;

	child = d_hash_and_lookup(dir, &qname);
	if (!child) {
		DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);
		child = d_alloc_parallel(dir, &qname, &wq);
		if (IS_ERR(child))
			goto end_instantiate;
		if (d_in_lookup(child)) {
			struct dentry *res;
			res = instantiate(child, task, ptr);
			d_lookup_done(child);
			if (unlikely(res)) {
				dput(child);
				child = res;
				if (IS_ERR(child))
					goto end_instantiate;
			}
		}
	}
	inode = d_inode(child);
	ino = inode->i_ino;
	type = inode->i_mode >> 12;
	dput(child);
end_instantiate:
	return dir_emit(ctx, name, len, ino, type);
}