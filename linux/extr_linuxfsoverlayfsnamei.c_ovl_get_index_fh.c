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
struct ovl_fs {int /*<<< orphan*/  indexdir; } ;
struct ovl_fh {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int) ; 
 int ESTALE ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  PTR_ERR (struct dentry*) ; 
 scalar_t__ d_is_negative (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct dentry* lookup_one_len_unlocked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ovl_dentry_weird (struct dentry*) ; 
 int ovl_get_index_name_fh (struct ovl_fh*,struct qstr*) ; 
 scalar_t__ ovl_is_whiteout (struct dentry*) ; 

struct dentry *ovl_get_index_fh(struct ovl_fs *ofs, struct ovl_fh *fh)
{
	struct dentry *index;
	struct qstr name;
	int err;

	err = ovl_get_index_name_fh(fh, &name);
	if (err)
		return ERR_PTR(err);

	index = lookup_one_len_unlocked(name.name, ofs->indexdir, name.len);
	kfree(name.name);
	if (IS_ERR(index)) {
		if (PTR_ERR(index) == -ENOENT)
			index = NULL;
		return index;
	}

	if (d_is_negative(index))
		err = 0;
	else if (ovl_is_whiteout(index))
		err = -ESTALE;
	else if (ovl_dentry_weird(index))
		err = -EIO;
	else
		return index;

	dput(index);
	return ERR_PTR(err);
}