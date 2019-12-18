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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int ENOSPC ; 
 int ocfs2_claim_clusters (int /*<<< orphan*/ *,struct ocfs2_alloc_context*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_block_group_claim_bits(struct ocfs2_super *osb,
					handle_t *handle,
					struct ocfs2_alloc_context *ac,
					unsigned int min_bits,
					u32 *bit_off, u32 *num_bits)
{
	int status = 0;

	while (min_bits) {
		status = ocfs2_claim_clusters(handle, ac, min_bits,
					      bit_off, num_bits);
		if (status != -ENOSPC)
			break;

		min_bits >>= 1;
	}

	return status;
}