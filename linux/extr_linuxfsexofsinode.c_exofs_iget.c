#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_fs_info; } ;
struct TYPE_7__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_6__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_5__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct inode {int i_state; scalar_t__ i_mode; scalar_t__ i_nlink; char* i_link; int /*<<< orphan*/ * i_op; TYPE_4__* i_mapping; int /*<<< orphan*/ * i_fop; void* i_rdev; scalar_t__ i_generation; int /*<<< orphan*/  i_blkbits; TYPE_3__ i_mtime; TYPE_2__ i_atime; TYPE_1__ i_ctime; } ;
struct exofs_i_info {scalar_t__ i_data; scalar_t__ i_dir_start_lookup; int /*<<< orphan*/  i_commit_size; int /*<<< orphan*/  one_comp; int /*<<< orphan*/  oc; } ;
struct exofs_fcb {scalar_t__* i_data; scalar_t__ i_generation; int /*<<< orphan*/  i_size; scalar_t__ i_mtime; scalar_t__ i_atime; scalar_t__ i_ctime; int /*<<< orphan*/  i_links_count; scalar_t__ i_gid; scalar_t__ i_uid; int /*<<< orphan*/  i_mode; } ;
struct TYPE_8__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 int ESTALE ; 
 int /*<<< orphan*/  EXOFS_BLKSHIFT ; 
 int I_NEW ; 
 scalar_t__ S_ISBLK (scalar_t__) ; 
 scalar_t__ S_ISCHR (scalar_t__) ; 
 scalar_t__ S_ISDIR (scalar_t__) ; 
 scalar_t__ S_ISLNK (scalar_t__) ; 
 scalar_t__ S_ISREG (scalar_t__) ; 
 int /*<<< orphan*/  __oi_init (struct exofs_i_info*) ; 
 int /*<<< orphan*/  exofs_aops ; 
 int /*<<< orphan*/  exofs_dir_inode_operations ; 
 int /*<<< orphan*/  exofs_dir_operations ; 
 int /*<<< orphan*/  exofs_file_inode_operations ; 
 int /*<<< orphan*/  exofs_file_operations ; 
 int exofs_get_inode (struct super_block*,struct exofs_i_info*,struct exofs_fcb*) ; 
 struct exofs_i_info* exofs_i (struct inode*) ; 
 int /*<<< orphan*/  exofs_init_comps (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ exofs_inode_is_fast_symlink (struct inode*) ; 
 int /*<<< orphan*/  exofs_oi_objno (struct exofs_i_info*) ; 
 int /*<<< orphan*/  exofs_special_inode_operations ; 
 int /*<<< orphan*/  i_gid_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_uid_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 struct inode* iget_locked (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,scalar_t__,void*) ; 
 int /*<<< orphan*/  inode_nohighmem (struct inode*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__*,int) ; 
 void* new_decode_dev (scalar_t__) ; 
 void* old_decode_dev (scalar_t__) ; 
 int /*<<< orphan*/  page_symlink_inode_operations ; 
 int /*<<< orphan*/  set_nlink (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  set_obj_created (struct exofs_i_info*) ; 
 int /*<<< orphan*/  simple_symlink_inode_operations ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *exofs_iget(struct super_block *sb, unsigned long ino)
{
	struct exofs_i_info *oi;
	struct exofs_fcb fcb;
	struct inode *inode;
	int ret;

	inode = iget_locked(sb, ino);
	if (!inode)
		return ERR_PTR(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		return inode;
	oi = exofs_i(inode);
	__oi_init(oi);
	exofs_init_comps(&oi->oc, &oi->one_comp, sb->s_fs_info,
			 exofs_oi_objno(oi));

	/* read the inode from the osd */
	ret = exofs_get_inode(sb, oi, &fcb);
	if (ret)
		goto bad_inode;

	set_obj_created(oi);

	/* copy stuff from on-disk struct to in-memory struct */
	inode->i_mode = le16_to_cpu(fcb.i_mode);
	i_uid_write(inode, le32_to_cpu(fcb.i_uid));
	i_gid_write(inode, le32_to_cpu(fcb.i_gid));
	set_nlink(inode, le16_to_cpu(fcb.i_links_count));
	inode->i_ctime.tv_sec = (signed)le32_to_cpu(fcb.i_ctime);
	inode->i_atime.tv_sec = (signed)le32_to_cpu(fcb.i_atime);
	inode->i_mtime.tv_sec = (signed)le32_to_cpu(fcb.i_mtime);
	inode->i_ctime.tv_nsec =
		inode->i_atime.tv_nsec = inode->i_mtime.tv_nsec = 0;
	oi->i_commit_size = le64_to_cpu(fcb.i_size);
	i_size_write(inode, oi->i_commit_size);
	inode->i_blkbits = EXOFS_BLKSHIFT;
	inode->i_generation = le32_to_cpu(fcb.i_generation);

	oi->i_dir_start_lookup = 0;

	if ((inode->i_nlink == 0) && (inode->i_mode == 0)) {
		ret = -ESTALE;
		goto bad_inode;
	}

	if (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode)) {
		if (fcb.i_data[0])
			inode->i_rdev =
				old_decode_dev(le32_to_cpu(fcb.i_data[0]));
		else
			inode->i_rdev =
				new_decode_dev(le32_to_cpu(fcb.i_data[1]));
	} else {
		memcpy(oi->i_data, fcb.i_data, sizeof(fcb.i_data));
	}

	if (S_ISREG(inode->i_mode)) {
		inode->i_op = &exofs_file_inode_operations;
		inode->i_fop = &exofs_file_operations;
		inode->i_mapping->a_ops = &exofs_aops;
	} else if (S_ISDIR(inode->i_mode)) {
		inode->i_op = &exofs_dir_inode_operations;
		inode->i_fop = &exofs_dir_operations;
		inode->i_mapping->a_ops = &exofs_aops;
	} else if (S_ISLNK(inode->i_mode)) {
		if (exofs_inode_is_fast_symlink(inode)) {
			inode->i_op = &simple_symlink_inode_operations;
			inode->i_link = (char *)oi->i_data;
		} else {
			inode->i_op = &page_symlink_inode_operations;
			inode_nohighmem(inode);
			inode->i_mapping->a_ops = &exofs_aops;
		}
	} else {
		inode->i_op = &exofs_special_inode_operations;
		if (fcb.i_data[0])
			init_special_inode(inode, inode->i_mode,
			   old_decode_dev(le32_to_cpu(fcb.i_data[0])));
		else
			init_special_inode(inode, inode->i_mode,
			   new_decode_dev(le32_to_cpu(fcb.i_data[1])));
	}

	unlock_new_inode(inode);
	return inode;

bad_inode:
	iget_failed(inode);
	return ERR_PTR(ret);
}