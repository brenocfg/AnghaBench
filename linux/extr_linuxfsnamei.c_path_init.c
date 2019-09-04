#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct dentry* dentry; int /*<<< orphan*/ * mnt; } ;
struct nameidata {unsigned int flags; scalar_t__ dfd; TYPE_3__ path; struct inode* inode; void* seq; void* m_seq; TYPE_3__ root; void* root_seq; scalar_t__ depth; int /*<<< orphan*/  last_type; TYPE_1__* name; } ;
struct inode {int dummy; } ;
struct fs_struct {TYPE_3__ pwd; int /*<<< orphan*/  seq; } ;
struct fd {TYPE_2__* file; } ;
struct dentry {struct inode* d_inode; int /*<<< orphan*/  d_seq; } ;
struct TYPE_9__ {struct fs_struct* fs; } ;
struct TYPE_7__ {TYPE_3__ f_path; } ;
struct TYPE_6__ {char* name; } ;

/* Variables and functions */
 scalar_t__ AT_FDCWD ; 
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  ECHILD ; 
 int /*<<< orphan*/  ENOTDIR ; 
 char const* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAST_ROOT ; 
 unsigned int LOOKUP_JUMPED ; 
 unsigned int LOOKUP_PARENT ; 
 unsigned int LOOKUP_RCU ; 
 unsigned int LOOKUP_ROOT ; 
 void* __read_seqcount_begin (int /*<<< orphan*/ *) ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  d_can_lookup (struct dentry*) ; 
 struct fd fdget_raw (scalar_t__) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int /*<<< orphan*/  get_fs_pwd (struct fs_struct*,TYPE_3__*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mount_lock ; 
 int /*<<< orphan*/  nd_jump_root (struct nameidata*) ; 
 int /*<<< orphan*/  path_get (TYPE_3__*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 void* read_seqbegin (int /*<<< orphan*/ *) ; 
 void* read_seqcount_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqcount_retry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  set_root (struct nameidata*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static const char *path_init(struct nameidata *nd, unsigned flags)
{
	const char *s = nd->name->name;

	if (!*s)
		flags &= ~LOOKUP_RCU;
	if (flags & LOOKUP_RCU)
		rcu_read_lock();

	nd->last_type = LAST_ROOT; /* if there are only slashes... */
	nd->flags = flags | LOOKUP_JUMPED | LOOKUP_PARENT;
	nd->depth = 0;
	if (flags & LOOKUP_ROOT) {
		struct dentry *root = nd->root.dentry;
		struct inode *inode = root->d_inode;
		if (*s && unlikely(!d_can_lookup(root)))
			return ERR_PTR(-ENOTDIR);
		nd->path = nd->root;
		nd->inode = inode;
		if (flags & LOOKUP_RCU) {
			nd->seq = __read_seqcount_begin(&nd->path.dentry->d_seq);
			nd->root_seq = nd->seq;
			nd->m_seq = read_seqbegin(&mount_lock);
		} else {
			path_get(&nd->path);
		}
		return s;
	}

	nd->root.mnt = NULL;
	nd->path.mnt = NULL;
	nd->path.dentry = NULL;

	nd->m_seq = read_seqbegin(&mount_lock);
	if (*s == '/') {
		set_root(nd);
		if (likely(!nd_jump_root(nd)))
			return s;
		return ERR_PTR(-ECHILD);
	} else if (nd->dfd == AT_FDCWD) {
		if (flags & LOOKUP_RCU) {
			struct fs_struct *fs = current->fs;
			unsigned seq;

			do {
				seq = read_seqcount_begin(&fs->seq);
				nd->path = fs->pwd;
				nd->inode = nd->path.dentry->d_inode;
				nd->seq = __read_seqcount_begin(&nd->path.dentry->d_seq);
			} while (read_seqcount_retry(&fs->seq, seq));
		} else {
			get_fs_pwd(current->fs, &nd->path);
			nd->inode = nd->path.dentry->d_inode;
		}
		return s;
	} else {
		/* Caller must check execute permissions on the starting path component */
		struct fd f = fdget_raw(nd->dfd);
		struct dentry *dentry;

		if (!f.file)
			return ERR_PTR(-EBADF);

		dentry = f.file->f_path.dentry;

		if (*s && unlikely(!d_can_lookup(dentry))) {
			fdput(f);
			return ERR_PTR(-ENOTDIR);
		}

		nd->path = f.file->f_path;
		if (flags & LOOKUP_RCU) {
			nd->inode = nd->path.dentry->d_inode;
			nd->seq = read_seqcount_begin(&nd->path.dentry->d_seq);
		} else {
			path_get(&nd->path);
			nd->inode = nd->path.dentry->d_inode;
		}
		fdput(f);
		return s;
	}
}