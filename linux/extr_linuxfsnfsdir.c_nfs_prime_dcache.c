#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct qstr {int len; char* name; int /*<<< orphan*/  hash; } ;
struct nfs_entry {int /*<<< orphan*/  label; TYPE_1__* fattr; TYPE_3__* fh; int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_8__ {int /*<<< orphan*/  fsid; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; } ;
struct TYPE_6__ {int valid; int /*<<< orphan*/  fsid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAIT_QUEUE_HEAD_ONSTACK (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int NFS_ATTR_FATTR_FILEID ; 
 int NFS_ATTR_FATTR_FSID ; 
 TYPE_5__* NFS_SB (int /*<<< orphan*/ ) ; 
 struct qstr QSTR_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dentry* d_alloc_parallel (struct dentry*,struct qstr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_in_lookup (struct dentry*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_invalidate (struct dentry*) ; 
 struct dentry* d_lookup (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  d_lookup_done (struct dentry*) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  full_name_hash (struct dentry*,char*,int) ; 
 struct inode* nfs_fhget (int /*<<< orphan*/ ,TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_fsid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nfs_refresh_inode (struct inode*,TYPE_1__*) ; 
 scalar_t__ nfs_same_file (struct dentry*,struct nfs_entry*) ; 
 int /*<<< orphan*/  nfs_save_change_attribute (struct inode*) ; 
 int /*<<< orphan*/  nfs_set_verifier (struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_setsecurity (struct inode*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strnchr (char*,int,char) ; 
 int strnlen (char*,int) ; 
 int /*<<< orphan*/  wq ; 

__attribute__((used)) static
void nfs_prime_dcache(struct dentry *parent, struct nfs_entry *entry)
{
	struct qstr filename = QSTR_INIT(entry->name, entry->len);
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);
	struct dentry *dentry;
	struct dentry *alias;
	struct inode *dir = d_inode(parent);
	struct inode *inode;
	int status;

	if (!(entry->fattr->valid & NFS_ATTR_FATTR_FILEID))
		return;
	if (!(entry->fattr->valid & NFS_ATTR_FATTR_FSID))
		return;
	if (filename.len == 0)
		return;
	/* Validate that the name doesn't contain any illegal '\0' */
	if (strnlen(filename.name, filename.len) != filename.len)
		return;
	/* ...or '/' */
	if (strnchr(filename.name, filename.len, '/'))
		return;
	if (filename.name[0] == '.') {
		if (filename.len == 1)
			return;
		if (filename.len == 2 && filename.name[1] == '.')
			return;
	}
	filename.hash = full_name_hash(parent, filename.name, filename.len);

	dentry = d_lookup(parent, &filename);
again:
	if (!dentry) {
		dentry = d_alloc_parallel(parent, &filename, &wq);
		if (IS_ERR(dentry))
			return;
	}
	if (!d_in_lookup(dentry)) {
		/* Is there a mountpoint here? If so, just exit */
		if (!nfs_fsid_equal(&NFS_SB(dentry->d_sb)->fsid,
					&entry->fattr->fsid))
			goto out;
		if (nfs_same_file(dentry, entry)) {
			if (!entry->fh->size)
				goto out;
			nfs_set_verifier(dentry, nfs_save_change_attribute(dir));
			status = nfs_refresh_inode(d_inode(dentry), entry->fattr);
			if (!status)
				nfs_setsecurity(d_inode(dentry), entry->fattr, entry->label);
			goto out;
		} else {
			d_invalidate(dentry);
			dput(dentry);
			dentry = NULL;
			goto again;
		}
	}
	if (!entry->fh->size) {
		d_lookup_done(dentry);
		goto out;
	}

	inode = nfs_fhget(dentry->d_sb, entry->fh, entry->fattr, entry->label);
	alias = d_splice_alias(inode, dentry);
	d_lookup_done(dentry);
	if (alias) {
		if (IS_ERR(alias))
			goto out;
		dput(dentry);
		dentry = alias;
	}
	nfs_set_verifier(dentry, nfs_save_change_attribute(dir));
out:
	dput(dentry);
}