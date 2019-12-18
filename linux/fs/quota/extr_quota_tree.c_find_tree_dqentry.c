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
typedef  int /*<<< orphan*/  uint ;
struct qtree_mem_dqinfo {int dqi_qtree_depth; int /*<<< orphan*/  dqi_usable_bs; } ;
struct dquot {int /*<<< orphan*/  dq_id; int /*<<< orphan*/  dq_sb; } ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 scalar_t__ find_block_dqentry (struct qtree_mem_dqinfo*,struct dquot*,int /*<<< orphan*/ ) ; 
 size_t get_index (struct qtree_mem_dqinfo*,int /*<<< orphan*/ ,int) ; 
 char* getdqbuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quota_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ read_blk (struct qtree_mem_dqinfo*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static loff_t find_tree_dqentry(struct qtree_mem_dqinfo *info,
				struct dquot *dquot, uint blk, int depth)
{
	char *buf = getdqbuf(info->dqi_usable_bs);
	loff_t ret = 0;
	__le32 *ref = (__le32 *)buf;

	if (!buf)
		return -ENOMEM;
	ret = read_blk(info, blk, buf);
	if (ret < 0) {
		quota_error(dquot->dq_sb, "Can't read quota tree block %u",
			    blk);
		goto out_buf;
	}
	ret = 0;
	blk = le32_to_cpu(ref[get_index(info, dquot->dq_id, depth)]);
	if (!blk)	/* No reference? */
		goto out_buf;
	if (depth < info->dqi_qtree_depth - 1)
		ret = find_tree_dqentry(info, dquot, blk, depth+1);
	else
		ret = find_block_dqentry(info, dquot, blk);
out_buf:
	kfree(buf);
	return ret;
}