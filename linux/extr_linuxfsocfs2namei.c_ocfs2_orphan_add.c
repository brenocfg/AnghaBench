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
struct ocfs2_super {int /*<<< orphan*/  slot_num; } ;
struct ocfs2_dir_lookup_result {int dummy; } ;
struct ocfs2_dinode {void* i_orphaned_slot; int /*<<< orphan*/  i_flags; void* i_dio_orphaned_slot; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {scalar_t__ ip_blkno; int /*<<< orphan*/  ip_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_DIO_ORPHANED_FL ; 
 int OCFS2_DIO_ORPHAN_PREFIX_LEN ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_INODE_SKIP_ORPHAN_DIR ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  OCFS2_ORPHANED_FL ; 
 int OCFS2_ORPHAN_NAMELEN ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int __ocfs2_add_entry (int /*<<< orphan*/ *,struct inode*,char*,int,struct inode*,scalar_t__,struct buffer_head*,struct ocfs2_dir_lookup_result*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_add_links_count (struct ocfs2_dinode*,int) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_read_inode_block (struct inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_read_links_count (struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ocfs2_orphan_add_begin (unsigned long long) ; 
 int /*<<< orphan*/  trace_ocfs2_orphan_add_end (unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_orphan_add(struct ocfs2_super *osb,
			    handle_t *handle,
			    struct inode *inode,
			    struct buffer_head *fe_bh,
			    char *name,
			    struct ocfs2_dir_lookup_result *lookup,
			    struct inode *orphan_dir_inode,
			    bool dio)
{
	struct buffer_head *orphan_dir_bh = NULL;
	int status = 0;
	struct ocfs2_dinode *orphan_fe;
	struct ocfs2_dinode *fe = (struct ocfs2_dinode *) fe_bh->b_data;
	int namelen = dio ?
			(OCFS2_DIO_ORPHAN_PREFIX_LEN + OCFS2_ORPHAN_NAMELEN) :
			OCFS2_ORPHAN_NAMELEN;

	trace_ocfs2_orphan_add_begin(
				(unsigned long long)OCFS2_I(inode)->ip_blkno);

	status = ocfs2_read_inode_block(orphan_dir_inode, &orphan_dir_bh);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	status = ocfs2_journal_access_di(handle,
					 INODE_CACHE(orphan_dir_inode),
					 orphan_dir_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	/*
	 * We're going to journal the change of i_flags and i_orphaned_slot.
	 * It's safe anyway, though some callers may duplicate the journaling.
	 * Journaling within the func just make the logic look more
	 * straightforward.
	 */
	status = ocfs2_journal_access_di(handle,
					 INODE_CACHE(inode),
					 fe_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	/* we're a cluster, and nlink can change on disk from
	 * underneath us... */
	orphan_fe = (struct ocfs2_dinode *) orphan_dir_bh->b_data;
	if (S_ISDIR(inode->i_mode))
		ocfs2_add_links_count(orphan_fe, 1);
	set_nlink(orphan_dir_inode, ocfs2_read_links_count(orphan_fe));
	ocfs2_journal_dirty(handle, orphan_dir_bh);

	status = __ocfs2_add_entry(handle, orphan_dir_inode, name,
				   namelen, inode,
				   OCFS2_I(inode)->ip_blkno,
				   orphan_dir_bh, lookup);
	if (status < 0) {
		mlog_errno(status);
		goto rollback;
	}

	if (dio) {
		/* Update flag OCFS2_DIO_ORPHANED_FL and record the orphan
		 * slot.
		 */
		fe->i_flags |= cpu_to_le32(OCFS2_DIO_ORPHANED_FL);
		fe->i_dio_orphaned_slot = cpu_to_le16(osb->slot_num);
	} else {
		fe->i_flags |= cpu_to_le32(OCFS2_ORPHANED_FL);
		OCFS2_I(inode)->ip_flags &= ~OCFS2_INODE_SKIP_ORPHAN_DIR;

		/* Record which orphan dir our inode now resides
		 * in. delete_inode will use this to determine which orphan
		 * dir to lock. */
		fe->i_orphaned_slot = cpu_to_le16(osb->slot_num);
	}

	ocfs2_journal_dirty(handle, fe_bh);

	trace_ocfs2_orphan_add_end((unsigned long long)OCFS2_I(inode)->ip_blkno,
				   osb->slot_num);

rollback:
	if (status < 0) {
		if (S_ISDIR(inode->i_mode))
			ocfs2_add_links_count(orphan_fe, -1);
		set_nlink(orphan_dir_inode, ocfs2_read_links_count(orphan_fe));
	}

leave:
	brelse(orphan_dir_bh);

	return status;
}