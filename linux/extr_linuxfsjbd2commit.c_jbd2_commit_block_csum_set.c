#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct commit_header {scalar_t__* h_chksum; scalar_t__ h_chksum_size; scalar_t__ h_chksum_type; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  j_blocksize; int /*<<< orphan*/  j_csum_seed; } ;
typedef  TYPE_1__ journal_t ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_chksum (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_journal_has_csum_v2or3 (TYPE_1__*) ; 

__attribute__((used)) static void jbd2_commit_block_csum_set(journal_t *j, struct buffer_head *bh)
{
	struct commit_header *h;
	__u32 csum;

	if (!jbd2_journal_has_csum_v2or3(j))
		return;

	h = (struct commit_header *)(bh->b_data);
	h->h_chksum_type = 0;
	h->h_chksum_size = 0;
	h->h_chksum[0] = 0;
	csum = jbd2_chksum(j, j->j_csum_seed, bh->b_data, j->j_blocksize);
	h->h_chksum[0] = cpu_to_be32(csum);
}