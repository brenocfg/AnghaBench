#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct recovery_info {int /*<<< orphan*/  nr_revokes; } ;
struct jbd2_journal_block_tail {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_9__ {int j_blocksize; } ;
typedef  TYPE_1__ journal_t ;
struct TYPE_10__ {int /*<<< orphan*/  r_count; } ;
typedef  TYPE_2__ jbd2_journal_revoke_header_t ;
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EFSBADCRC ; 
 int EINVAL ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long long be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_descriptor_block_csum_verify (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ jbd2_has_feature_64bit (TYPE_1__*) ; 
 scalar_t__ jbd2_journal_has_csum_v2or3 (TYPE_1__*) ; 
 int jbd2_journal_set_revoke (TYPE_1__*,unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scan_revoke_records(journal_t *journal, struct buffer_head *bh,
			       tid_t sequence, struct recovery_info *info)
{
	jbd2_journal_revoke_header_t *header;
	int offset, max;
	int csum_size = 0;
	__u32 rcount;
	int record_len = 4;

	header = (jbd2_journal_revoke_header_t *) bh->b_data;
	offset = sizeof(jbd2_journal_revoke_header_t);
	rcount = be32_to_cpu(header->r_count);

	if (!jbd2_descriptor_block_csum_verify(journal, header))
		return -EFSBADCRC;

	if (jbd2_journal_has_csum_v2or3(journal))
		csum_size = sizeof(struct jbd2_journal_block_tail);
	if (rcount > journal->j_blocksize - csum_size)
		return -EINVAL;
	max = rcount;

	if (jbd2_has_feature_64bit(journal))
		record_len = 8;

	while (offset + record_len <= max) {
		unsigned long long blocknr;
		int err;

		if (record_len == 4)
			blocknr = be32_to_cpu(* ((__be32 *) (bh->b_data+offset)));
		else
			blocknr = be64_to_cpu(* ((__be64 *) (bh->b_data+offset)));
		offset += record_len;
		err = jbd2_journal_set_revoke(journal, blocknr, sequence);
		if (err)
			return err;
		++info->nr_revokes;
	}
	return 0;
}