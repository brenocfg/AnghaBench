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
struct ubifs_info {int fanout; int max_idx_node_sz; } ;

/* Variables and functions */
 int UBIFS_BLOCK_SIZE ; 
 int UBIFS_MAX_DATA_NODE_SZ ; 
 long long div_u64 (long long,int) ; 

long long ubifs_reported_space(const struct ubifs_info *c, long long free)
{
	int divisor, factor, f;

	/*
	 * Reported space size is @free * X, where X is UBIFS block size
	 * divided by UBIFS block size + all overhead one data block
	 * introduces. The overhead is the node header + indexing overhead.
	 *
	 * Indexing overhead calculations are based on the following formula:
	 * I = N/(f - 1) + 1, where I - number of indexing nodes, N - number
	 * of data nodes, f - fanout. Because effective UBIFS fanout is twice
	 * as less than maximum fanout, we assume that each data node
	 * introduces 3 * @c->max_idx_node_sz / (@c->fanout/2 - 1) bytes.
	 * Note, the multiplier 3 is because UBIFS reserves thrice as more space
	 * for the index.
	 */
	f = c->fanout > 3 ? c->fanout >> 1 : 2;
	factor = UBIFS_BLOCK_SIZE;
	divisor = UBIFS_MAX_DATA_NODE_SZ;
	divisor += (c->max_idx_node_sz * 3) / (f - 1);
	free *= factor;
	return div_u64(free, divisor);
}