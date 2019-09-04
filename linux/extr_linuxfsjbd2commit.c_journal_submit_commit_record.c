#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  transaction_t ;
struct timespec64 {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct commit_header {void** h_chksum; int /*<<< orphan*/  h_chksum_size; int /*<<< orphan*/  h_chksum_type; void* h_commit_nsec; int /*<<< orphan*/  h_commit_sec; } ;
struct buffer_head {int /*<<< orphan*/  b_end_io; scalar_t__ b_data; } ;
struct TYPE_7__ {int j_flags; } ;
typedef  TYPE_1__ journal_t ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int JBD2_BARRIER ; 
 int /*<<< orphan*/  JBD2_COMMIT_BLOCK ; 
 int /*<<< orphan*/  JBD2_CRC32_CHKSUM ; 
 int /*<<< orphan*/  JBD2_CRC32_CHKSUM_SIZE ; 
 int REQ_FUA ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int REQ_PREFLUSH ; 
 int REQ_SYNC ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_journal_aborted (TYPE_1__*) ; 
 int /*<<< orphan*/  jbd2_commit_block_csum_set (TYPE_1__*,struct buffer_head*) ; 
 int /*<<< orphan*/  jbd2_has_feature_async_commit (TYPE_1__*) ; 
 scalar_t__ jbd2_has_feature_checksum (TYPE_1__*) ; 
 struct buffer_head* jbd2_journal_get_descriptor_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  journal_end_buffer_io_sync ; 
 int /*<<< orphan*/  ktime_get_coarse_real_ts64 (struct timespec64*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int submit_bh (int /*<<< orphan*/ ,int,struct buffer_head*) ; 

__attribute__((used)) static int journal_submit_commit_record(journal_t *journal,
					transaction_t *commit_transaction,
					struct buffer_head **cbh,
					__u32 crc32_sum)
{
	struct commit_header *tmp;
	struct buffer_head *bh;
	int ret;
	struct timespec64 now;

	*cbh = NULL;

	if (is_journal_aborted(journal))
		return 0;

	bh = jbd2_journal_get_descriptor_buffer(commit_transaction,
						JBD2_COMMIT_BLOCK);
	if (!bh)
		return 1;

	tmp = (struct commit_header *)bh->b_data;
	ktime_get_coarse_real_ts64(&now);
	tmp->h_commit_sec = cpu_to_be64(now.tv_sec);
	tmp->h_commit_nsec = cpu_to_be32(now.tv_nsec);

	if (jbd2_has_feature_checksum(journal)) {
		tmp->h_chksum_type 	= JBD2_CRC32_CHKSUM;
		tmp->h_chksum_size 	= JBD2_CRC32_CHKSUM_SIZE;
		tmp->h_chksum[0] 	= cpu_to_be32(crc32_sum);
	}
	jbd2_commit_block_csum_set(journal, bh);

	BUFFER_TRACE(bh, "submit commit block");
	lock_buffer(bh);
	clear_buffer_dirty(bh);
	set_buffer_uptodate(bh);
	bh->b_end_io = journal_end_buffer_io_sync;

	if (journal->j_flags & JBD2_BARRIER &&
	    !jbd2_has_feature_async_commit(journal))
		ret = submit_bh(REQ_OP_WRITE,
			REQ_SYNC | REQ_PREFLUSH | REQ_FUA, bh);
	else
		ret = submit_bh(REQ_OP_WRITE, REQ_SYNC, bh);

	*cbh = bh;
	return ret;
}