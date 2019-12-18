#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct super_block {int s_flags; } ;
struct stat_data {int dummy; } ;
struct reiserfs_transaction_handle {int displace_new_blocks; scalar_t__ t_trans_id; } ;
struct reiserfs_security_handle {scalar_t__ name; } ;
struct reiserfs_iget_args {void* objectid; void* dirid; } ;
struct TYPE_9__ {scalar_t__ k_objectid; scalar_t__ k_dir_id; } ;
struct item_head {TYPE_3__ ih_key; } ;
struct inode {int /*<<< orphan*/  i_flags; struct super_block* i_sb; int /*<<< orphan*/  i_size; scalar_t__ i_bytes; scalar_t__ i_blocks; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; void* i_generation; void* i_ino; int /*<<< orphan*/  i_nlink; } ;
struct dentry {int dummy; } ;
struct cpu_key {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_11__ {int i_first_direct_byte; int i_attrs; scalar_t__ new_packing_locality; int /*<<< orphan*/ * i_jl; scalar_t__ i_trans_id; scalar_t__ i_prealloc_count; scalar_t__ i_prealloc_block; scalar_t__ i_flags; int /*<<< orphan*/  i_prealloc_list; } ;
struct TYPE_10__ {TYPE_1__* s_rs; } ;
struct TYPE_8__ {scalar_t__ k_objectid; } ;
struct TYPE_7__ {scalar_t__ s_inode_generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EEXIST ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  INITIALIZE_PATH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_2__* INODE_PKEY (struct inode*) ; 
 int IO_ERROR ; 
 scalar_t__ IS_PRIVATE (struct inode*) ; 
 int ITEM_FOUND ; 
 int /*<<< orphan*/  KEY_FORMAT_3_5 ; 
 int /*<<< orphan*/  KEY_FORMAT_3_6 ; 
 int /*<<< orphan*/  KEY_SIZE ; 
 int /*<<< orphan*/  MAX_US_INT ; 
 TYPE_5__* REISERFS_I (struct inode*) ; 
 int REISERFS_INHERIT_MASK ; 
 TYPE_4__* REISERFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  ROUND_UP (int /*<<< orphan*/ ) ; 
 int SB_POSIXACL ; 
 int /*<<< orphan*/  SD_OFFSET ; 
 int /*<<< orphan*/  SD_SIZE ; 
 int /*<<< orphan*/  SD_V1_SIZE ; 
 int /*<<< orphan*/  STAT_DATA_V1 ; 
 int /*<<< orphan*/  STAT_DATA_V2 ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_NOQUOTA ; 
 int /*<<< orphan*/  S_PRIVATE ; 
 int /*<<< orphan*/  TYPE_STAT_DATA ; 
 int U32_MAX ; 
 int /*<<< orphan*/  _make_cpu_key (struct cpu_key*,int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int dquot_alloc_inode (struct inode*) ; 
 int /*<<< orphan*/  dquot_drop (struct inode*) ; 
 int /*<<< orphan*/  dquot_free_inode (struct inode*) ; 
 void* event ; 
 int i_gid_read (struct inode*) ; 
 int i_uid_read (struct inode*) ; 
 int /*<<< orphan*/  inode2sd (struct stat_data*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode2sd_v1 (struct stat_data*,struct inode*,int /*<<< orphan*/ ) ; 
 int insert_inode_locked4 (struct inode*,void*,int /*<<< orphan*/ ,struct reiserfs_iget_args*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int journal_end (struct reiserfs_transaction_handle*) ; 
 void* le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  make_le_item_head (struct item_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ old_format_only (struct super_block*) ; 
 int /*<<< orphan*/  path_to_key ; 
 int /*<<< orphan*/  pathrelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reiserfs_check_path (int /*<<< orphan*/ *) ; 
 scalar_t__ reiserfs_choose_packing (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_find_actor ; 
 int /*<<< orphan*/  reiserfs_get_unused_objectid (struct reiserfs_transaction_handle*) ; 
 int reiserfs_inherit_default_acl (struct reiserfs_transaction_handle*,struct inode*,struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  reiserfs_init_xattr_rwsem (struct inode*) ; 
 int reiserfs_insert_item (struct reiserfs_transaction_handle*,int /*<<< orphan*/ *,struct cpu_key*,struct item_head*,struct inode*,char*) ; 
 int reiserfs_new_directory (struct reiserfs_transaction_handle*,struct inode*,struct item_head*,int /*<<< orphan*/ *,struct inode*) ; 
 int reiserfs_new_symlink (struct reiserfs_transaction_handle*,struct inode*,struct item_head*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ reiserfs_posixacl (struct super_block*) ; 
 int reiserfs_security_write (struct reiserfs_transaction_handle*,struct inode*,struct reiserfs_security_handle*) ; 
 int /*<<< orphan*/  reiserfs_update_sd (struct reiserfs_transaction_handle*,struct inode*) ; 
 int /*<<< orphan*/  reiserfs_warning (struct super_block*,char*,char*) ; 
 int /*<<< orphan*/  reiserfs_write_lock (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_write_lock_nested (struct super_block*,int) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (struct super_block*) ; 
 int reiserfs_write_unlock_nested (struct super_block*) ; 
 int /*<<< orphan*/  sd_attrs_to_i_attrs (int,struct inode*) ; 
 int search_item (struct super_block*,struct cpu_key*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_inode_item_key_version (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_inode_sd_version (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

int reiserfs_new_inode(struct reiserfs_transaction_handle *th,
		       struct inode *dir, umode_t mode, const char *symname,
		       /* 0 for regular, EMTRY_DIR_SIZE for dirs,
		          strlen (symname) for symlinks) */
		       loff_t i_size, struct dentry *dentry,
		       struct inode *inode,
		       struct reiserfs_security_handle *security)
{
	struct super_block *sb = dir->i_sb;
	struct reiserfs_iget_args args;
	INITIALIZE_PATH(path_to_key);
	struct cpu_key key;
	struct item_head ih;
	struct stat_data sd;
	int retval;
	int err;
	int depth;

	BUG_ON(!th->t_trans_id);

	depth = reiserfs_write_unlock_nested(sb);
	err = dquot_alloc_inode(inode);
	reiserfs_write_lock_nested(sb, depth);
	if (err)
		goto out_end_trans;
	if (!dir->i_nlink) {
		err = -EPERM;
		goto out_bad_inode;
	}

	/* item head of new item */
	ih.ih_key.k_dir_id = reiserfs_choose_packing(dir);
	ih.ih_key.k_objectid = cpu_to_le32(reiserfs_get_unused_objectid(th));
	if (!ih.ih_key.k_objectid) {
		err = -ENOMEM;
		goto out_bad_inode;
	}
	args.objectid = inode->i_ino = le32_to_cpu(ih.ih_key.k_objectid);
	if (old_format_only(sb))
		make_le_item_head(&ih, NULL, KEY_FORMAT_3_5, SD_OFFSET,
				  TYPE_STAT_DATA, SD_V1_SIZE, MAX_US_INT);
	else
		make_le_item_head(&ih, NULL, KEY_FORMAT_3_6, SD_OFFSET,
				  TYPE_STAT_DATA, SD_SIZE, MAX_US_INT);
	memcpy(INODE_PKEY(inode), &ih.ih_key, KEY_SIZE);
	args.dirid = le32_to_cpu(ih.ih_key.k_dir_id);

	depth = reiserfs_write_unlock_nested(inode->i_sb);
	err = insert_inode_locked4(inode, args.objectid,
			     reiserfs_find_actor, &args);
	reiserfs_write_lock_nested(inode->i_sb, depth);
	if (err) {
		err = -EINVAL;
		goto out_bad_inode;
	}

	if (old_format_only(sb))
		/*
		 * not a perfect generation count, as object ids can be reused,
		 * but this is as good as reiserfs can do right now.
		 * note that the private part of inode isn't filled in yet,
		 * we have to use the directory.
		 */
		inode->i_generation = le32_to_cpu(INODE_PKEY(dir)->k_objectid);
	else
#if defined( USE_INODE_GENERATION_COUNTER )
		inode->i_generation =
		    le32_to_cpu(REISERFS_SB(sb)->s_rs->s_inode_generation);
#else
		inode->i_generation = ++event;
#endif

	/* fill stat data */
	set_nlink(inode, (S_ISDIR(mode) ? 2 : 1));

	/* uid and gid must already be set by the caller for quota init */

	inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);
	inode->i_size = i_size;
	inode->i_blocks = 0;
	inode->i_bytes = 0;
	REISERFS_I(inode)->i_first_direct_byte = S_ISLNK(mode) ? 1 :
	    U32_MAX /*NO_BYTES_IN_DIRECT_ITEM */ ;

	INIT_LIST_HEAD(&REISERFS_I(inode)->i_prealloc_list);
	REISERFS_I(inode)->i_flags = 0;
	REISERFS_I(inode)->i_prealloc_block = 0;
	REISERFS_I(inode)->i_prealloc_count = 0;
	REISERFS_I(inode)->i_trans_id = 0;
	REISERFS_I(inode)->i_jl = NULL;
	REISERFS_I(inode)->i_attrs =
	    REISERFS_I(dir)->i_attrs & REISERFS_INHERIT_MASK;
	sd_attrs_to_i_attrs(REISERFS_I(inode)->i_attrs, inode);
	reiserfs_init_xattr_rwsem(inode);

	/* key to search for correct place for new stat data */
	_make_cpu_key(&key, KEY_FORMAT_3_6, le32_to_cpu(ih.ih_key.k_dir_id),
		      le32_to_cpu(ih.ih_key.k_objectid), SD_OFFSET,
		      TYPE_STAT_DATA, 3 /*key length */ );

	/* find proper place for inserting of stat data */
	retval = search_item(sb, &key, &path_to_key);
	if (retval == IO_ERROR) {
		err = -EIO;
		goto out_bad_inode;
	}
	if (retval == ITEM_FOUND) {
		pathrelse(&path_to_key);
		err = -EEXIST;
		goto out_bad_inode;
	}
	if (old_format_only(sb)) {
		/* i_uid or i_gid is too big to be stored in stat data v3.5 */
		if (i_uid_read(inode) & ~0xffff || i_gid_read(inode) & ~0xffff) {
			pathrelse(&path_to_key);
			err = -EINVAL;
			goto out_bad_inode;
		}
		inode2sd_v1(&sd, inode, inode->i_size);
	} else {
		inode2sd(&sd, inode, inode->i_size);
	}
	/*
	 * store in in-core inode the key of stat data and version all
	 * object items will have (directory items will have old offset
	 * format, other new objects will consist of new items)
	 */
	if (old_format_only(sb) || S_ISDIR(mode) || S_ISLNK(mode))
		set_inode_item_key_version(inode, KEY_FORMAT_3_5);
	else
		set_inode_item_key_version(inode, KEY_FORMAT_3_6);
	if (old_format_only(sb))
		set_inode_sd_version(inode, STAT_DATA_V1);
	else
		set_inode_sd_version(inode, STAT_DATA_V2);

	/* insert the stat data into the tree */
#ifdef DISPLACE_NEW_PACKING_LOCALITIES
	if (REISERFS_I(dir)->new_packing_locality)
		th->displace_new_blocks = 1;
#endif
	retval =
	    reiserfs_insert_item(th, &path_to_key, &key, &ih, inode,
				 (char *)(&sd));
	if (retval) {
		err = retval;
		reiserfs_check_path(&path_to_key);
		goto out_bad_inode;
	}
#ifdef DISPLACE_NEW_PACKING_LOCALITIES
	if (!th->displace_new_blocks)
		REISERFS_I(dir)->new_packing_locality = 0;
#endif
	if (S_ISDIR(mode)) {
		/* insert item with "." and ".." */
		retval =
		    reiserfs_new_directory(th, inode, &ih, &path_to_key, dir);
	}

	if (S_ISLNK(mode)) {
		/* insert body of symlink */
		if (!old_format_only(sb))
			i_size = ROUND_UP(i_size);
		retval =
		    reiserfs_new_symlink(th, inode, &ih, &path_to_key, symname,
					 i_size);
	}
	if (retval) {
		err = retval;
		reiserfs_check_path(&path_to_key);
		journal_end(th);
		goto out_inserted_sd;
	}

	if (reiserfs_posixacl(inode->i_sb)) {
		reiserfs_write_unlock(inode->i_sb);
		retval = reiserfs_inherit_default_acl(th, dir, dentry, inode);
		reiserfs_write_lock(inode->i_sb);
		if (retval) {
			err = retval;
			reiserfs_check_path(&path_to_key);
			journal_end(th);
			goto out_inserted_sd;
		}
	} else if (inode->i_sb->s_flags & SB_POSIXACL) {
		reiserfs_warning(inode->i_sb, "jdm-13090",
				 "ACLs aren't enabled in the fs, "
				 "but vfs thinks they are!");
	} else if (IS_PRIVATE(dir))
		inode->i_flags |= S_PRIVATE;

	if (security->name) {
		reiserfs_write_unlock(inode->i_sb);
		retval = reiserfs_security_write(th, inode, security);
		reiserfs_write_lock(inode->i_sb);
		if (retval) {
			err = retval;
			reiserfs_check_path(&path_to_key);
			retval = journal_end(th);
			if (retval)
				err = retval;
			goto out_inserted_sd;
		}
	}

	reiserfs_update_sd(th, inode);
	reiserfs_check_path(&path_to_key);

	return 0;

out_bad_inode:
	/* Invalidate the object, nothing was inserted yet */
	INODE_PKEY(inode)->k_objectid = 0;

	/* Quota change must be inside a transaction for journaling */
	depth = reiserfs_write_unlock_nested(inode->i_sb);
	dquot_free_inode(inode);
	reiserfs_write_lock_nested(inode->i_sb, depth);

out_end_trans:
	journal_end(th);
	/*
	 * Drop can be outside and it needs more credits so it's better
	 * to have it outside
	 */
	depth = reiserfs_write_unlock_nested(inode->i_sb);
	dquot_drop(inode);
	reiserfs_write_lock_nested(inode->i_sb, depth);
	inode->i_flags |= S_NOQUOTA;
	make_bad_inode(inode);

out_inserted_sd:
	clear_nlink(inode);
	th->t_trans_id = 0;	/* so the caller can't use this handle later */
	unlock_new_inode(inode); /* OK to do even if we hadn't locked it */
	iput(inode);
	return err;
}