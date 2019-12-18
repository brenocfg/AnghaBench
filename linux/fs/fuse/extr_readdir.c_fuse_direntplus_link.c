#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct qstr {char* name; int len; int /*<<< orphan*/  hash; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_sb; } ;
struct fuse_inode {int /*<<< orphan*/  state; int /*<<< orphan*/  lock; int /*<<< orphan*/  nlookup; } ;
struct TYPE_5__ {int mode; } ;
struct fuse_entry_out {scalar_t__ nodeid; TYPE_2__ attr; int /*<<< orphan*/  generation; } ;
struct fuse_dirent {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct fuse_direntplus {struct fuse_dirent dirent; struct fuse_entry_out entry_out; } ;
struct fuse_conn {scalar_t__ readdirplus_auto; } ;
struct TYPE_4__ {struct dentry* dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAIT_QUEUE_HEAD_ONSTACK (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FUSE_I_INIT_RDPLUS ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 struct qstr QSTR_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int S_IFMT ; 
 struct dentry* d_alloc_parallel (struct dentry*,struct qstr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_in_lookup (struct dentry*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_invalidate (struct dentry*) ; 
 struct dentry* d_lookup (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  d_lookup_done (struct dentry*) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  entry_attr_timeout (struct fuse_entry_out*) ; 
 int /*<<< orphan*/  forget_all_cached_acls (struct inode*) ; 
 int /*<<< orphan*/  full_name_hash (struct dentry*,char*,int) ; 
 int /*<<< orphan*/  fuse_change_attributes (struct inode*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_change_entry_timeout (struct dentry*,struct fuse_entry_out*) ; 
 struct inode* fuse_iget (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_valid_type (int) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 scalar_t__ get_node_id (struct inode*) ; 
 scalar_t__ invalid_nodeid (scalar_t__) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wq ; 

__attribute__((used)) static int fuse_direntplus_link(struct file *file,
				struct fuse_direntplus *direntplus,
				u64 attr_version)
{
	struct fuse_entry_out *o = &direntplus->entry_out;
	struct fuse_dirent *dirent = &direntplus->dirent;
	struct dentry *parent = file->f_path.dentry;
	struct qstr name = QSTR_INIT(dirent->name, dirent->namelen);
	struct dentry *dentry;
	struct dentry *alias;
	struct inode *dir = d_inode(parent);
	struct fuse_conn *fc;
	struct inode *inode;
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);

	if (!o->nodeid) {
		/*
		 * Unlike in the case of fuse_lookup, zero nodeid does not mean
		 * ENOENT. Instead, it only means the userspace filesystem did
		 * not want to return attributes/handle for this entry.
		 *
		 * So do nothing.
		 */
		return 0;
	}

	if (name.name[0] == '.') {
		/*
		 * We could potentially refresh the attributes of the directory
		 * and its parent?
		 */
		if (name.len == 1)
			return 0;
		if (name.name[1] == '.' && name.len == 2)
			return 0;
	}

	if (invalid_nodeid(o->nodeid))
		return -EIO;
	if (!fuse_valid_type(o->attr.mode))
		return -EIO;

	fc = get_fuse_conn(dir);

	name.hash = full_name_hash(parent, name.name, name.len);
	dentry = d_lookup(parent, &name);
	if (!dentry) {
retry:
		dentry = d_alloc_parallel(parent, &name, &wq);
		if (IS_ERR(dentry))
			return PTR_ERR(dentry);
	}
	if (!d_in_lookup(dentry)) {
		struct fuse_inode *fi;
		inode = d_inode(dentry);
		if (!inode ||
		    get_node_id(inode) != o->nodeid ||
		    ((o->attr.mode ^ inode->i_mode) & S_IFMT)) {
			d_invalidate(dentry);
			dput(dentry);
			goto retry;
		}
		if (is_bad_inode(inode)) {
			dput(dentry);
			return -EIO;
		}

		fi = get_fuse_inode(inode);
		spin_lock(&fi->lock);
		fi->nlookup++;
		spin_unlock(&fi->lock);

		forget_all_cached_acls(inode);
		fuse_change_attributes(inode, &o->attr,
				       entry_attr_timeout(o),
				       attr_version);
		/*
		 * The other branch comes via fuse_iget()
		 * which bumps nlookup inside
		 */
	} else {
		inode = fuse_iget(dir->i_sb, o->nodeid, o->generation,
				  &o->attr, entry_attr_timeout(o),
				  attr_version);
		if (!inode)
			inode = ERR_PTR(-ENOMEM);

		alias = d_splice_alias(inode, dentry);
		d_lookup_done(dentry);
		if (alias) {
			dput(dentry);
			dentry = alias;
		}
		if (IS_ERR(dentry))
			return PTR_ERR(dentry);
	}
	if (fc->readdirplus_auto)
		set_bit(FUSE_I_INIT_RDPLUS, &get_fuse_inode(inode)->state);
	fuse_change_entry_timeout(dentry, o);

	dput(dentry);
	return 0;
}