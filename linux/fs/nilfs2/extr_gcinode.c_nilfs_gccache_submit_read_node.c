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
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  scalar_t__ __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  i_btnode_cache; } ;

/* Variables and functions */
 int EEXIST ; 
 TYPE_1__* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int nilfs_btnode_submit_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**,int /*<<< orphan*/ *) ; 

int nilfs_gccache_submit_read_node(struct inode *inode, sector_t pbn,
				   __u64 vbn, struct buffer_head **out_bh)
{
	int ret;

	ret = nilfs_btnode_submit_block(&NILFS_I(inode)->i_btnode_cache,
					vbn ? : pbn, pbn, REQ_OP_READ, 0,
					out_bh, &pbn);
	if (ret == -EEXIST) /* internal code (cache hit) */
		ret = 0;
	return ret;
}