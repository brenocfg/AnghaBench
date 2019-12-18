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
struct super_block {int dummy; } ;
struct reiserfs_transaction_handle {int /*<<< orphan*/  t_trans_id; struct super_block* t_super; } ;
struct reiserfs_super_block {int dummy; } ;
typedef  scalar_t__ __u32 ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SB_BUFFER_WITH_SB (struct super_block*) ; 
 struct reiserfs_super_block* SB_DISK_SUPER_BLOCK (struct super_block*) ; 
 scalar_t__ U32_MAX ; 
 int /*<<< orphan*/  check_objectid_map (struct super_block*,scalar_t__*) ; 
 scalar_t__ cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  journal_mark_dirty (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__* objectid_map (struct super_block*,struct reiserfs_super_block*) ; 
 int /*<<< orphan*/  reiserfs_prepare_for_journal (struct super_block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reiserfs_restore_prepared_buffer (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_warning (struct super_block*,char*,char*) ; 
 int sb_oid_cursize (struct reiserfs_super_block*) ; 
 int /*<<< orphan*/  set_sb_oid_cursize (struct reiserfs_super_block*,int) ; 

__u32 reiserfs_get_unused_objectid(struct reiserfs_transaction_handle *th)
{
	struct super_block *s = th->t_super;
	struct reiserfs_super_block *rs = SB_DISK_SUPER_BLOCK(s);
	__le32 *map = objectid_map(s, rs);
	__u32 unused_objectid;

	BUG_ON(!th->t_trans_id);

	check_objectid_map(s, map);

	reiserfs_prepare_for_journal(s, SB_BUFFER_WITH_SB(s), 1);
	/* comment needed -Hans */
	unused_objectid = le32_to_cpu(map[1]);
	if (unused_objectid == U32_MAX) {
		reiserfs_warning(s, "reiserfs-15100", "no more object ids");
		reiserfs_restore_prepared_buffer(s, SB_BUFFER_WITH_SB(s));
		return 0;
	}

	/*
	 * This incrementation allocates the first unused objectid. That
	 * is to say, the first entry on the objectid map is the first
	 * unused objectid, and by incrementing it we use it.  See below
	 * where we check to see if we eliminated a sequence of unused
	 * objectids....
	 */
	map[1] = cpu_to_le32(unused_objectid + 1);

	/*
	 * Now we check to see if we eliminated the last remaining member of
	 * the first even sequence (and can eliminate the sequence by
	 * eliminating its last objectid from oids), and can collapse the
	 * first two odd sequences into one sequence.  If so, then the net
	 * result is to eliminate a pair of objectids from oids.  We do this
	 * by shifting the entire map to the left.
	 */
	if (sb_oid_cursize(rs) > 2 && map[1] == map[2]) {
		memmove(map + 1, map + 3,
			(sb_oid_cursize(rs) - 3) * sizeof(__u32));
		set_sb_oid_cursize(rs, sb_oid_cursize(rs) - 2);
	}

	journal_mark_dirty(th, SB_BUFFER_WITH_SB(s));
	return unused_objectid;
}