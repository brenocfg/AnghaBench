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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int i_mode; } ;
struct fuse_inode {int /*<<< orphan*/  state; int /*<<< orphan*/  lock; int /*<<< orphan*/  nlookup; } ;
struct fuse_forget_link {int dummy; } ;
struct TYPE_2__ {int mode; } ;
struct fuse_entry_out {scalar_t__ nodeid; TYPE_1__ attr; } ;
struct fuse_conn {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int ECHILD ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FUSE_ARGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FUSE_I_INIT_RDPLUS ; 
 unsigned int LOOKUP_RCU ; 
 unsigned int LOOKUP_REVAL ; 
 int S_IFMT ; 
 int /*<<< orphan*/  args ; 
 struct inode* d_inode (struct dentry*) ; 
 struct inode* d_inode_rcu (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  entry_attr_timeout (struct fuse_entry_out*) ; 
 int /*<<< orphan*/  forget_all_cached_acls (struct inode*) ; 
 int /*<<< orphan*/  fuse_advise_use_readdirplus (struct inode*) ; 
 struct fuse_forget_link* fuse_alloc_forget () ; 
 int /*<<< orphan*/  fuse_change_attributes (struct inode*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_change_entry_timeout (struct dentry*,struct fuse_entry_out*) ; 
 int /*<<< orphan*/  fuse_dentry_time (struct dentry*) ; 
 int /*<<< orphan*/  fuse_get_attr_version (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_lookup_init (struct fuse_conn*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,struct fuse_entry_out*) ; 
 int /*<<< orphan*/  fuse_queue_forget (struct fuse_conn*,struct fuse_forget_link*,scalar_t__,int) ; 
 int fuse_simple_request (struct fuse_conn*,int /*<<< orphan*/ *) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  get_jiffies_64 () ; 
 scalar_t__ get_node_id (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct fuse_forget_link*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_before64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fuse_dentry_revalidate(struct dentry *entry, unsigned int flags)
{
	struct inode *inode;
	struct dentry *parent;
	struct fuse_conn *fc;
	struct fuse_inode *fi;
	int ret;

	inode = d_inode_rcu(entry);
	if (inode && is_bad_inode(inode))
		goto invalid;
	else if (time_before64(fuse_dentry_time(entry), get_jiffies_64()) ||
		 (flags & LOOKUP_REVAL)) {
		struct fuse_entry_out outarg;
		FUSE_ARGS(args);
		struct fuse_forget_link *forget;
		u64 attr_version;

		/* For negative dentries, always do a fresh lookup */
		if (!inode)
			goto invalid;

		ret = -ECHILD;
		if (flags & LOOKUP_RCU)
			goto out;

		fc = get_fuse_conn(inode);

		forget = fuse_alloc_forget();
		ret = -ENOMEM;
		if (!forget)
			goto out;

		attr_version = fuse_get_attr_version(fc);

		parent = dget_parent(entry);
		fuse_lookup_init(fc, &args, get_node_id(d_inode(parent)),
				 &entry->d_name, &outarg);
		ret = fuse_simple_request(fc, &args);
		dput(parent);
		/* Zero nodeid is same as -ENOENT */
		if (!ret && !outarg.nodeid)
			ret = -ENOENT;
		if (!ret) {
			fi = get_fuse_inode(inode);
			if (outarg.nodeid != get_node_id(inode)) {
				fuse_queue_forget(fc, forget, outarg.nodeid, 1);
				goto invalid;
			}
			spin_lock(&fi->lock);
			fi->nlookup++;
			spin_unlock(&fi->lock);
		}
		kfree(forget);
		if (ret == -ENOMEM)
			goto out;
		if (ret || (outarg.attr.mode ^ inode->i_mode) & S_IFMT)
			goto invalid;

		forget_all_cached_acls(inode);
		fuse_change_attributes(inode, &outarg.attr,
				       entry_attr_timeout(&outarg),
				       attr_version);
		fuse_change_entry_timeout(entry, &outarg);
	} else if (inode) {
		fi = get_fuse_inode(inode);
		if (flags & LOOKUP_RCU) {
			if (test_bit(FUSE_I_INIT_RDPLUS, &fi->state))
				return -ECHILD;
		} else if (test_and_clear_bit(FUSE_I_INIT_RDPLUS, &fi->state)) {
			parent = dget_parent(entry);
			fuse_advise_use_readdirplus(d_inode(parent));
			dput(parent);
		}
	}
	ret = 1;
out:
	return ret;

invalid:
	ret = 0;
	goto out;
}