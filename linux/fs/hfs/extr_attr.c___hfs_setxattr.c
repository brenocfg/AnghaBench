#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct hfs_find_data {int /*<<< orphan*/  entryoffset; int /*<<< orphan*/  bnode; TYPE_1__* search_key; } ;
struct TYPE_9__ {int /*<<< orphan*/  fdCreator; int /*<<< orphan*/  fdType; } ;
struct hfs_cat_file {TYPE_2__ UsrWds; } ;
struct TYPE_10__ {struct hfs_cat_file file; } ;
typedef  TYPE_3__ hfs_cat_rec ;
typedef  enum hfs_xattr_type { ____Placeholder_hfs_xattr_type } hfs_xattr_type ;
struct TYPE_12__ {int /*<<< orphan*/  cat_key; } ;
struct TYPE_11__ {int /*<<< orphan*/  cat_tree; } ;
struct TYPE_8__ {int /*<<< orphan*/  cat; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ERANGE ; 
#define  HFS_CREATOR 129 
 TYPE_7__* HFS_I (struct inode*) ; 
 scalar_t__ HFS_IS_RSRC (struct inode*) ; 
 TYPE_6__* HFS_SB (int /*<<< orphan*/ ) ; 
#define  HFS_TYPE 128 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_bnode_read (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hfs_bnode_write (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int hfs_brec_find (struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 

__attribute__((used)) static int __hfs_setxattr(struct inode *inode, enum hfs_xattr_type type,
			  const void *value, size_t size, int flags)
{
	struct hfs_find_data fd;
	hfs_cat_rec rec;
	struct hfs_cat_file *file;
	int res;

	if (!S_ISREG(inode->i_mode) || HFS_IS_RSRC(inode))
		return -EOPNOTSUPP;

	res = hfs_find_init(HFS_SB(inode->i_sb)->cat_tree, &fd);
	if (res)
		return res;
	fd.search_key->cat = HFS_I(inode)->cat_key;
	res = hfs_brec_find(&fd);
	if (res)
		goto out;
	hfs_bnode_read(fd.bnode, &rec, fd.entryoffset,
			sizeof(struct hfs_cat_file));
	file = &rec.file;

	switch (type) {
	case HFS_TYPE:
		if (size == 4)
			memcpy(&file->UsrWds.fdType, value, 4);
		else
			res = -ERANGE;
		break;

	case HFS_CREATOR:
		if (size == 4)
			memcpy(&file->UsrWds.fdCreator, value, 4);
		else
			res = -ERANGE;
		break;
	}

	if (!res)
		hfs_bnode_write(fd.bnode, &rec, fd.entryoffset,
				sizeof(struct hfs_cat_file));
out:
	hfs_find_exit(&fd);
	return res;
}