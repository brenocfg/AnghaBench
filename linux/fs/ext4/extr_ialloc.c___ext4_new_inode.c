#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* umode_t ;
typedef  int /*<<< orphan*/  uid_t ;
struct super_block {int dummy; } ;
struct qstr {int dummy; } ;
struct posix_acl {int a_count; TYPE_3__* h_transaction; int /*<<< orphan*/  b_data; } ;
struct inode {unsigned long i_ino; unsigned long i_generation; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; scalar_t__ i_blocks; struct super_block* i_sb; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; void* i_mode; int /*<<< orphan*/  i_nlink; } ;
struct ext4_sb_info {int s_inode_goal; int s_csum_seed; int /*<<< orphan*/  s_want_extra_isize; TYPE_2__* s_flex_groups; scalar_t__ s_log_groups_per_flex; int /*<<< orphan*/  s_dirs_counter; int /*<<< orphan*/  s_freeinodes_counter; TYPE_1__* s_es; scalar_t__ s_journal; } ;
struct ext4_inode_info {size_t i_last_alloc_group; int i_flags; size_t i_block_group; int /*<<< orphan*/  i_datasync_tid; int /*<<< orphan*/  i_sync_tid; scalar_t__ i_inline_off; int /*<<< orphan*/  i_extra_isize; void* i_csum_seed; scalar_t__ i_dtime; scalar_t__ i_file_acl; scalar_t__ i_disksize; scalar_t__ i_dir_start_lookup; int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_crtime; int /*<<< orphan*/  i_projid; } ;
struct ext4_group_info {int /*<<< orphan*/  alloc_sem; } ;
struct ext4_group_desc {int bg_flags; } ;
struct buffer_head {int a_count; TYPE_3__* h_transaction; int /*<<< orphan*/  b_data; } ;
typedef  int /*<<< orphan*/  inum ;
typedef  struct posix_acl handle_t ;
typedef  int /*<<< orphan*/  gen ;
typedef  size_t ext4_group_t ;
typedef  int /*<<< orphan*/  ext4_acl_entry ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_6__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_5__ {int /*<<< orphan*/  free_inodes; int /*<<< orphan*/  used_dirs; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_inodes_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int /*<<< orphan*/  BUFFER_TRACE (struct posix_acl*,char*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DUMMY_ENCRYPTION_ENABLED (struct ext4_sb_info*) ; 
 int EIO ; 
 int ENOKEY ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int EPERM ; 
 struct inode* ERR_CAST (struct posix_acl*) ; 
 struct inode* ERR_PTR (int) ; 
 int /*<<< orphan*/  EXT4_BG_BLOCK_UNINIT ; 
 int /*<<< orphan*/  EXT4_BG_INODE_UNINIT ; 
 int /*<<< orphan*/  EXT4_DEF_PROJID ; 
 int EXT4_EA_INODE_FL ; 
 unsigned long EXT4_FIRST_INO (struct super_block*) ; 
 int EXT4_FL_INHERITED ; 
 int /*<<< orphan*/  EXT4_GROUP_INFO_IBITMAP_CORRUPT ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 size_t EXT4_INODES_PER_GROUP (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int /*<<< orphan*/  EXT4_INODE_PROJINHERIT ; 
 scalar_t__ EXT4_MB_GRP_IBITMAP_CORRUPT (struct ext4_group_info*) ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_STATE_MAY_INLINE_DATA ; 
 int /*<<< orphan*/  EXT4_STATE_NEW ; 
 int FSCRYPT_SET_CONTEXT_MAX_SIZE ; 
 int /*<<< orphan*/  GRPID ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 scalar_t__ IS_ENCRYPTED (struct inode*) ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int PTR_ERR (struct posix_acl*) ; 
 scalar_t__ S_ISDIR (void*) ; 
 scalar_t__ S_ISLNK (void*) ; 
 scalar_t__ S_ISREG (void*) ; 
 int /*<<< orphan*/  S_NOQUOTA ; 
 struct posix_acl* __ext4_journal_start_sb (struct super_block*,unsigned int,int,int,int /*<<< orphan*/ ) ; 
 int __ext4_xattr_set_credits (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct posix_acl*) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned long) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int dquot_alloc_inode (struct inode*) ; 
 int /*<<< orphan*/  dquot_drop (struct inode*) ; 
 int /*<<< orphan*/  dquot_free_inode (struct inode*) ; 
 int dquot_initialize (struct inode*) ; 
 int /*<<< orphan*/  ext4_block_bitmap_csum_set (struct super_block*,size_t,struct ext4_group_desc*,struct posix_acl*) ; 
 void* ext4_chksum (struct ext4_sb_info*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ext4_clear_state_flags (struct ext4_inode_info*) ; 
 int /*<<< orphan*/  ext4_debug (char*,unsigned long) ; 
 int /*<<< orphan*/  ext4_error (struct super_block*,char*,unsigned long) ; 
 int /*<<< orphan*/  ext4_ext_tree_init (struct posix_acl*,struct inode*) ; 
 size_t ext4_flex_group (struct ext4_sb_info*,size_t) ; 
 int /*<<< orphan*/  ext4_forced_shutdown (struct ext4_sb_info*) ; 
 int /*<<< orphan*/  ext4_free_clusters_after_init (struct super_block*,size_t,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_free_group_clusters_set (struct super_block*,struct ext4_group_desc*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_free_inodes_count (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_free_inodes_set (struct super_block*,struct ext4_group_desc*,scalar_t__) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,size_t,struct posix_acl**) ; 
 struct ext4_group_info* ext4_get_group_info (struct super_block*,size_t) ; 
 size_t ext4_get_groups_count (struct super_block*) ; 
 int /*<<< orphan*/  ext4_group_desc_csum_set (struct super_block*,size_t,struct ext4_group_desc*) ; 
 int ext4_handle_dirty_metadata (struct posix_acl*,int /*<<< orphan*/ *,struct posix_acl*) ; 
 int /*<<< orphan*/  ext4_handle_sync (struct posix_acl*) ; 
 scalar_t__ ext4_handle_valid (struct posix_acl*) ; 
 scalar_t__ ext4_has_feature_extents (struct super_block*) ; 
 scalar_t__ ext4_has_feature_inline_data (struct super_block*) ; 
 scalar_t__ ext4_has_feature_project (struct super_block*) ; 
 scalar_t__ ext4_has_group_desc_csum (struct super_block*) ; 
 scalar_t__ ext4_has_metadata_csum (struct super_block*) ; 
 int ext4_init_acl (struct posix_acl*,struct inode*,struct inode*) ; 
 int ext4_init_security (struct posix_acl*,struct inode*,struct inode*,struct qstr const*) ; 
 int /*<<< orphan*/  ext4_inode_bitmap_csum_set (struct super_block*,size_t,struct ext4_group_desc*,struct posix_acl*,int) ; 
 size_t ext4_itable_unused_count (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_itable_unused_set (struct super_block*,struct ext4_group_desc*,unsigned long) ; 
 int ext4_journal_get_write_access (struct posix_acl*,struct posix_acl*) ; 
 int /*<<< orphan*/  ext4_lock_group (struct super_block*,size_t) ; 
 int /*<<< orphan*/  ext4_mark_group_bitmap_corrupted (struct super_block*,size_t,int /*<<< orphan*/ ) ; 
 int ext4_mark_inode_dirty (struct posix_acl*,struct inode*) ; 
 int ext4_mask_flags (void*,int) ; 
 struct posix_acl* ext4_read_block_bitmap (struct super_block*,size_t) ; 
 struct posix_acl* ext4_read_inode_bitmap (struct super_block*,size_t) ; 
 int /*<<< orphan*/  ext4_set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_set_inode_flags (struct inode*) ; 
 int /*<<< orphan*/  ext4_set_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_std_error (struct super_block*,int) ; 
 int ext4_test_and_set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_unlock_group (struct super_block*,size_t) ; 
 scalar_t__ ext4_used_dirs_count (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_used_dirs_set (struct super_block*,struct ext4_group_desc*,scalar_t__) ; 
 int find_group_orlov (struct super_block*,struct inode*,size_t*,void*,struct qstr const*) ; 
 int find_group_other (struct super_block*,struct inode*,size_t*,void*) ; 
 int find_inode_bit (struct super_block*,size_t,struct posix_acl*,unsigned long*) ; 
 int fscrypt_get_encryption_info (struct inode*) ; 
 int /*<<< orphan*/  fscrypt_has_encryption_key (struct inode*) ; 
 int fscrypt_inherit_context (struct inode*,struct inode*,struct posix_acl*,int) ; 
 struct posix_acl* get_acl (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_gid_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_uid_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  inode_init_owner (struct inode*,struct inode*,void*) ; 
 scalar_t__ insert_inode_locked (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kprojid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  percpu_counter_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_counter_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 unsigned long prandom_u32 () ; 
 scalar_t__ test_opt (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext4_allocate_inode (struct inode*,struct inode*,void*) ; 
 int /*<<< orphan*/  trace_ext4_request_inode (struct inode*,void*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct inode *__ext4_new_inode(handle_t *handle, struct inode *dir,
			       umode_t mode, const struct qstr *qstr,
			       __u32 goal, uid_t *owner, __u32 i_flags,
			       int handle_type, unsigned int line_no,
			       int nblocks)
{
	struct super_block *sb;
	struct buffer_head *inode_bitmap_bh = NULL;
	struct buffer_head *group_desc_bh;
	ext4_group_t ngroups, group = 0;
	unsigned long ino = 0;
	struct inode *inode;
	struct ext4_group_desc *gdp = NULL;
	struct ext4_inode_info *ei;
	struct ext4_sb_info *sbi;
	int ret2, err;
	struct inode *ret;
	ext4_group_t i;
	ext4_group_t flex_group;
	struct ext4_group_info *grp;
	int encrypt = 0;

	/* Cannot create files in a deleted directory */
	if (!dir || !dir->i_nlink)
		return ERR_PTR(-EPERM);

	sb = dir->i_sb;
	sbi = EXT4_SB(sb);

	if (unlikely(ext4_forced_shutdown(sbi)))
		return ERR_PTR(-EIO);

	if ((IS_ENCRYPTED(dir) || DUMMY_ENCRYPTION_ENABLED(sbi)) &&
	    (S_ISREG(mode) || S_ISDIR(mode) || S_ISLNK(mode)) &&
	    !(i_flags & EXT4_EA_INODE_FL)) {
		err = fscrypt_get_encryption_info(dir);
		if (err)
			return ERR_PTR(err);
		if (!fscrypt_has_encryption_key(dir))
			return ERR_PTR(-ENOKEY);
		encrypt = 1;
	}

	if (!handle && sbi->s_journal && !(i_flags & EXT4_EA_INODE_FL)) {
#ifdef CONFIG_EXT4_FS_POSIX_ACL
		struct posix_acl *p = get_acl(dir, ACL_TYPE_DEFAULT);

		if (IS_ERR(p))
			return ERR_CAST(p);
		if (p) {
			int acl_size = p->a_count * sizeof(ext4_acl_entry);

			nblocks += (S_ISDIR(mode) ? 2 : 1) *
				__ext4_xattr_set_credits(sb, NULL /* inode */,
					NULL /* block_bh */, acl_size,
					true /* is_create */);
			posix_acl_release(p);
		}
#endif

#ifdef CONFIG_SECURITY
		{
			int num_security_xattrs = 1;

#ifdef CONFIG_INTEGRITY
			num_security_xattrs++;
#endif
			/*
			 * We assume that security xattrs are never
			 * more than 1k.  In practice they are under
			 * 128 bytes.
			 */
			nblocks += num_security_xattrs *
				__ext4_xattr_set_credits(sb, NULL /* inode */,
					NULL /* block_bh */, 1024,
					true /* is_create */);
		}
#endif
		if (encrypt)
			nblocks += __ext4_xattr_set_credits(sb,
					NULL /* inode */, NULL /* block_bh */,
					FSCRYPT_SET_CONTEXT_MAX_SIZE,
					true /* is_create */);
	}

	ngroups = ext4_get_groups_count(sb);
	trace_ext4_request_inode(dir, mode);
	inode = new_inode(sb);
	if (!inode)
		return ERR_PTR(-ENOMEM);
	ei = EXT4_I(inode);

	/*
	 * Initialize owners and quota early so that we don't have to account
	 * for quota initialization worst case in standard inode creating
	 * transaction
	 */
	if (owner) {
		inode->i_mode = mode;
		i_uid_write(inode, owner[0]);
		i_gid_write(inode, owner[1]);
	} else if (test_opt(sb, GRPID)) {
		inode->i_mode = mode;
		inode->i_uid = current_fsuid();
		inode->i_gid = dir->i_gid;
	} else
		inode_init_owner(inode, dir, mode);

	if (ext4_has_feature_project(sb) &&
	    ext4_test_inode_flag(dir, EXT4_INODE_PROJINHERIT))
		ei->i_projid = EXT4_I(dir)->i_projid;
	else
		ei->i_projid = make_kprojid(&init_user_ns, EXT4_DEF_PROJID);

	err = dquot_initialize(inode);
	if (err)
		goto out;

	if (!goal)
		goal = sbi->s_inode_goal;

	if (goal && goal <= le32_to_cpu(sbi->s_es->s_inodes_count)) {
		group = (goal - 1) / EXT4_INODES_PER_GROUP(sb);
		ino = (goal - 1) % EXT4_INODES_PER_GROUP(sb);
		ret2 = 0;
		goto got_group;
	}

	if (S_ISDIR(mode))
		ret2 = find_group_orlov(sb, dir, &group, mode, qstr);
	else
		ret2 = find_group_other(sb, dir, &group, mode);

got_group:
	EXT4_I(dir)->i_last_alloc_group = group;
	err = -ENOSPC;
	if (ret2 == -1)
		goto out;

	/*
	 * Normally we will only go through one pass of this loop,
	 * unless we get unlucky and it turns out the group we selected
	 * had its last inode grabbed by someone else.
	 */
	for (i = 0; i < ngroups; i++, ino = 0) {
		err = -EIO;

		gdp = ext4_get_group_desc(sb, group, &group_desc_bh);
		if (!gdp)
			goto out;

		/*
		 * Check free inodes count before loading bitmap.
		 */
		if (ext4_free_inodes_count(sb, gdp) == 0)
			goto next_group;

		grp = ext4_get_group_info(sb, group);
		/* Skip groups with already-known suspicious inode tables */
		if (EXT4_MB_GRP_IBITMAP_CORRUPT(grp))
			goto next_group;

		brelse(inode_bitmap_bh);
		inode_bitmap_bh = ext4_read_inode_bitmap(sb, group);
		/* Skip groups with suspicious inode tables */
		if (EXT4_MB_GRP_IBITMAP_CORRUPT(grp) ||
		    IS_ERR(inode_bitmap_bh)) {
			inode_bitmap_bh = NULL;
			goto next_group;
		}

repeat_in_this_group:
		ret2 = find_inode_bit(sb, group, inode_bitmap_bh, &ino);
		if (!ret2)
			goto next_group;

		if (group == 0 && (ino + 1) < EXT4_FIRST_INO(sb)) {
			ext4_error(sb, "reserved inode found cleared - "
				   "inode=%lu", ino + 1);
			ext4_mark_group_bitmap_corrupted(sb, group,
					EXT4_GROUP_INFO_IBITMAP_CORRUPT);
			goto next_group;
		}

		if (!handle) {
			BUG_ON(nblocks <= 0);
			handle = __ext4_journal_start_sb(dir->i_sb, line_no,
							 handle_type, nblocks,
							 0);
			if (IS_ERR(handle)) {
				err = PTR_ERR(handle);
				ext4_std_error(sb, err);
				goto out;
			}
		}
		BUFFER_TRACE(inode_bitmap_bh, "get_write_access");
		err = ext4_journal_get_write_access(handle, inode_bitmap_bh);
		if (err) {
			ext4_std_error(sb, err);
			goto out;
		}
		ext4_lock_group(sb, group);
		ret2 = ext4_test_and_set_bit(ino, inode_bitmap_bh->b_data);
		if (ret2) {
			/* Someone already took the bit. Repeat the search
			 * with lock held.
			 */
			ret2 = find_inode_bit(sb, group, inode_bitmap_bh, &ino);
			if (ret2) {
				ext4_set_bit(ino, inode_bitmap_bh->b_data);
				ret2 = 0;
			} else {
				ret2 = 1; /* we didn't grab the inode */
			}
		}
		ext4_unlock_group(sb, group);
		ino++;		/* the inode bitmap is zero-based */
		if (!ret2)
			goto got; /* we grabbed the inode! */

		if (ino < EXT4_INODES_PER_GROUP(sb))
			goto repeat_in_this_group;
next_group:
		if (++group == ngroups)
			group = 0;
	}
	err = -ENOSPC;
	goto out;

got:
	BUFFER_TRACE(inode_bitmap_bh, "call ext4_handle_dirty_metadata");
	err = ext4_handle_dirty_metadata(handle, NULL, inode_bitmap_bh);
	if (err) {
		ext4_std_error(sb, err);
		goto out;
	}

	BUFFER_TRACE(group_desc_bh, "get_write_access");
	err = ext4_journal_get_write_access(handle, group_desc_bh);
	if (err) {
		ext4_std_error(sb, err);
		goto out;
	}

	/* We may have to initialize the block bitmap if it isn't already */
	if (ext4_has_group_desc_csum(sb) &&
	    gdp->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT)) {
		struct buffer_head *block_bitmap_bh;

		block_bitmap_bh = ext4_read_block_bitmap(sb, group);
		if (IS_ERR(block_bitmap_bh)) {
			err = PTR_ERR(block_bitmap_bh);
			goto out;
		}
		BUFFER_TRACE(block_bitmap_bh, "get block bitmap access");
		err = ext4_journal_get_write_access(handle, block_bitmap_bh);
		if (err) {
			brelse(block_bitmap_bh);
			ext4_std_error(sb, err);
			goto out;
		}

		BUFFER_TRACE(block_bitmap_bh, "dirty block bitmap");
		err = ext4_handle_dirty_metadata(handle, NULL, block_bitmap_bh);

		/* recheck and clear flag under lock if we still need to */
		ext4_lock_group(sb, group);
		if (ext4_has_group_desc_csum(sb) &&
		    (gdp->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT))) {
			gdp->bg_flags &= cpu_to_le16(~EXT4_BG_BLOCK_UNINIT);
			ext4_free_group_clusters_set(sb, gdp,
				ext4_free_clusters_after_init(sb, group, gdp));
			ext4_block_bitmap_csum_set(sb, group, gdp,
						   block_bitmap_bh);
			ext4_group_desc_csum_set(sb, group, gdp);
		}
		ext4_unlock_group(sb, group);
		brelse(block_bitmap_bh);

		if (err) {
			ext4_std_error(sb, err);
			goto out;
		}
	}

	/* Update the relevant bg descriptor fields */
	if (ext4_has_group_desc_csum(sb)) {
		int free;
		struct ext4_group_info *grp = ext4_get_group_info(sb, group);

		down_read(&grp->alloc_sem); /* protect vs itable lazyinit */
		ext4_lock_group(sb, group); /* while we modify the bg desc */
		free = EXT4_INODES_PER_GROUP(sb) -
			ext4_itable_unused_count(sb, gdp);
		if (gdp->bg_flags & cpu_to_le16(EXT4_BG_INODE_UNINIT)) {
			gdp->bg_flags &= cpu_to_le16(~EXT4_BG_INODE_UNINIT);
			free = 0;
		}
		/*
		 * Check the relative inode number against the last used
		 * relative inode number in this group. if it is greater
		 * we need to update the bg_itable_unused count
		 */
		if (ino > free)
			ext4_itable_unused_set(sb, gdp,
					(EXT4_INODES_PER_GROUP(sb) - ino));
		up_read(&grp->alloc_sem);
	} else {
		ext4_lock_group(sb, group);
	}

	ext4_free_inodes_set(sb, gdp, ext4_free_inodes_count(sb, gdp) - 1);
	if (S_ISDIR(mode)) {
		ext4_used_dirs_set(sb, gdp, ext4_used_dirs_count(sb, gdp) + 1);
		if (sbi->s_log_groups_per_flex) {
			ext4_group_t f = ext4_flex_group(sbi, group);

			atomic_inc(&sbi->s_flex_groups[f].used_dirs);
		}
	}
	if (ext4_has_group_desc_csum(sb)) {
		ext4_inode_bitmap_csum_set(sb, group, gdp, inode_bitmap_bh,
					   EXT4_INODES_PER_GROUP(sb) / 8);
		ext4_group_desc_csum_set(sb, group, gdp);
	}
	ext4_unlock_group(sb, group);

	BUFFER_TRACE(group_desc_bh, "call ext4_handle_dirty_metadata");
	err = ext4_handle_dirty_metadata(handle, NULL, group_desc_bh);
	if (err) {
		ext4_std_error(sb, err);
		goto out;
	}

	percpu_counter_dec(&sbi->s_freeinodes_counter);
	if (S_ISDIR(mode))
		percpu_counter_inc(&sbi->s_dirs_counter);

	if (sbi->s_log_groups_per_flex) {
		flex_group = ext4_flex_group(sbi, group);
		atomic_dec(&sbi->s_flex_groups[flex_group].free_inodes);
	}

	inode->i_ino = ino + group * EXT4_INODES_PER_GROUP(sb);
	/* This is the optimal IO size (for stat), not the fs block size */
	inode->i_blocks = 0;
	inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);
	ei->i_crtime = inode->i_mtime;

	memset(ei->i_data, 0, sizeof(ei->i_data));
	ei->i_dir_start_lookup = 0;
	ei->i_disksize = 0;

	/* Don't inherit extent flag from directory, amongst others. */
	ei->i_flags =
		ext4_mask_flags(mode, EXT4_I(dir)->i_flags & EXT4_FL_INHERITED);
	ei->i_flags |= i_flags;
	ei->i_file_acl = 0;
	ei->i_dtime = 0;
	ei->i_block_group = group;
	ei->i_last_alloc_group = ~0;

	ext4_set_inode_flags(inode);
	if (IS_DIRSYNC(inode))
		ext4_handle_sync(handle);
	if (insert_inode_locked(inode) < 0) {
		/*
		 * Likely a bitmap corruption causing inode to be allocated
		 * twice.
		 */
		err = -EIO;
		ext4_error(sb, "failed to insert inode %lu: doubly allocated?",
			   inode->i_ino);
		ext4_mark_group_bitmap_corrupted(sb, group,
					EXT4_GROUP_INFO_IBITMAP_CORRUPT);
		goto out;
	}
	inode->i_generation = prandom_u32();

	/* Precompute checksum seed for inode metadata */
	if (ext4_has_metadata_csum(sb)) {
		__u32 csum;
		__le32 inum = cpu_to_le32(inode->i_ino);
		__le32 gen = cpu_to_le32(inode->i_generation);
		csum = ext4_chksum(sbi, sbi->s_csum_seed, (__u8 *)&inum,
				   sizeof(inum));
		ei->i_csum_seed = ext4_chksum(sbi, csum, (__u8 *)&gen,
					      sizeof(gen));
	}

	ext4_clear_state_flags(ei); /* Only relevant on 32-bit archs */
	ext4_set_inode_state(inode, EXT4_STATE_NEW);

	ei->i_extra_isize = sbi->s_want_extra_isize;
	ei->i_inline_off = 0;
	if (ext4_has_feature_inline_data(sb))
		ext4_set_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA);
	ret = inode;
	err = dquot_alloc_inode(inode);
	if (err)
		goto fail_drop;

	/*
	 * Since the encryption xattr will always be unique, create it first so
	 * that it's less likely to end up in an external xattr block and
	 * prevent its deduplication.
	 */
	if (encrypt) {
		err = fscrypt_inherit_context(dir, inode, handle, true);
		if (err)
			goto fail_free_drop;
	}

	if (!(ei->i_flags & EXT4_EA_INODE_FL)) {
		err = ext4_init_acl(handle, inode, dir);
		if (err)
			goto fail_free_drop;

		err = ext4_init_security(handle, inode, dir, qstr);
		if (err)
			goto fail_free_drop;
	}

	if (ext4_has_feature_extents(sb)) {
		/* set extent flag only for directory, file and normal symlink*/
		if (S_ISDIR(mode) || S_ISREG(mode) || S_ISLNK(mode)) {
			ext4_set_inode_flag(inode, EXT4_INODE_EXTENTS);
			ext4_ext_tree_init(handle, inode);
		}
	}

	if (ext4_handle_valid(handle)) {
		ei->i_sync_tid = handle->h_transaction->t_tid;
		ei->i_datasync_tid = handle->h_transaction->t_tid;
	}

	err = ext4_mark_inode_dirty(handle, inode);
	if (err) {
		ext4_std_error(sb, err);
		goto fail_free_drop;
	}

	ext4_debug("allocating inode %lu\n", inode->i_ino);
	trace_ext4_allocate_inode(inode, dir, mode);
	brelse(inode_bitmap_bh);
	return ret;

fail_free_drop:
	dquot_free_inode(inode);
fail_drop:
	clear_nlink(inode);
	unlock_new_inode(inode);
out:
	dquot_drop(inode);
	inode->i_flags |= S_NOQUOTA;
	iput(inode);
	brelse(inode_bitmap_bh);
	return ERR_PTR(err);
}