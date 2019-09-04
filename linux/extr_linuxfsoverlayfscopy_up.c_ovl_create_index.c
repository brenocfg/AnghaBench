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
struct qstr {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  OVL_CATTR (int) ; 
 int /*<<< orphan*/  OVL_INDEX ; 
 int PTR_ERR (struct dentry*) ; 
 int S_IFDIR ; 
 scalar_t__ WARN_ON (int) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_is_dir (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct dentry* lookup_one_len (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_cleanup (struct inode*,struct dentry*) ; 
 struct dentry* ovl_create_temp (struct dentry*,int /*<<< orphan*/ ) ; 
 int ovl_do_rename (struct inode*,struct dentry*,struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
 int ovl_get_index_name (struct dentry*,struct qstr*) ; 
 struct dentry* ovl_indexdir (int /*<<< orphan*/ ) ; 
 int ovl_set_upper_fh (struct dentry*,struct dentry*) ; 
 int ovl_test_flag (int /*<<< orphan*/ ,struct inode*) ; 

__attribute__((used)) static int ovl_create_index(struct dentry *dentry, struct dentry *origin,
			    struct dentry *upper)
{
	struct dentry *indexdir = ovl_indexdir(dentry->d_sb);
	struct inode *dir = d_inode(indexdir);
	struct dentry *index = NULL;
	struct dentry *temp = NULL;
	struct qstr name = { };
	int err;

	/*
	 * For now this is only used for creating index entry for directories,
	 * because non-dir are copied up directly to index and then hardlinked
	 * to upper dir.
	 *
	 * TODO: implement create index for non-dir, so we can call it when
	 * encoding file handle for non-dir in case index does not exist.
	 */
	if (WARN_ON(!d_is_dir(dentry)))
		return -EIO;

	/* Directory not expected to be indexed before copy up */
	if (WARN_ON(ovl_test_flag(OVL_INDEX, d_inode(dentry))))
		return -EIO;

	err = ovl_get_index_name(origin, &name);
	if (err)
		return err;

	temp = ovl_create_temp(indexdir, OVL_CATTR(S_IFDIR | 0));
	err = PTR_ERR(temp);
	if (IS_ERR(temp))
		goto free_name;

	err = ovl_set_upper_fh(upper, temp);
	if (err)
		goto out;

	index = lookup_one_len(name.name, indexdir, name.len);
	if (IS_ERR(index)) {
		err = PTR_ERR(index);
	} else {
		err = ovl_do_rename(dir, temp, dir, index, 0);
		dput(index);
	}
out:
	if (err)
		ovl_cleanup(dir, temp);
	dput(temp);
free_name:
	kfree(name.name);
	return err;
}