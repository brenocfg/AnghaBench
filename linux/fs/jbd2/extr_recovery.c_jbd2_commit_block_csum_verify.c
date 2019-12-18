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
struct commit_header {scalar_t__* h_chksum; } ;
struct TYPE_5__ {int /*<<< orphan*/  j_blocksize; int /*<<< orphan*/  j_csum_seed; } ;
typedef  TYPE_1__ journal_t ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_chksum (TYPE_1__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_journal_has_csum_v2or3 (TYPE_1__*) ; 

__attribute__((used)) static int jbd2_commit_block_csum_verify(journal_t *j, void *buf)
{
	struct commit_header *h;
	__be32 provided;
	__u32 calculated;

	if (!jbd2_journal_has_csum_v2or3(j))
		return 1;

	h = buf;
	provided = h->h_chksum[0];
	h->h_chksum[0] = 0;
	calculated = jbd2_chksum(j, j->j_csum_seed, buf, j->j_blocksize);
	h->h_chksum[0] = provided;

	return provided == cpu_to_be32(calculated);
}