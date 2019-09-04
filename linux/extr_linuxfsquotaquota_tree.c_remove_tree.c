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
struct qtree_mem_dqinfo {int dqi_usable_bs; int dqi_qtree_depth; } ;
struct dquot {int /*<<< orphan*/  dq_sb; int /*<<< orphan*/  dq_id; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  QT_TREEOFF ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int free_dqentry (struct qtree_mem_dqinfo*,struct dquot*,int /*<<< orphan*/ ) ; 
 size_t get_index (struct qtree_mem_dqinfo*,int /*<<< orphan*/ ,int) ; 
 char* getdqbuf (int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_free_dqblk (struct qtree_mem_dqinfo*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quota_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int read_blk (struct qtree_mem_dqinfo*,int /*<<< orphan*/ ,char*) ; 
 int write_blk (struct qtree_mem_dqinfo*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int remove_tree(struct qtree_mem_dqinfo *info, struct dquot *dquot,
		       uint *blk, int depth)
{
	char *buf = getdqbuf(info->dqi_usable_bs);
	int ret = 0;
	uint newblk;
	__le32 *ref = (__le32 *)buf;

	if (!buf)
		return -ENOMEM;
	ret = read_blk(info, *blk, buf);
	if (ret < 0) {
		quota_error(dquot->dq_sb, "Can't read quota data block %u",
			    *blk);
		goto out_buf;
	}
	newblk = le32_to_cpu(ref[get_index(info, dquot->dq_id, depth)]);
	if (depth == info->dqi_qtree_depth - 1) {
		ret = free_dqentry(info, dquot, newblk);
		newblk = 0;
	} else {
		ret = remove_tree(info, dquot, &newblk, depth+1);
	}
	if (ret >= 0 && !newblk) {
		int i;
		ref[get_index(info, dquot->dq_id, depth)] = cpu_to_le32(0);
		/* Block got empty? */
		for (i = 0; i < (info->dqi_usable_bs >> 2) && !ref[i]; i++)
			;
		/* Don't put the root block into the free block list */
		if (i == (info->dqi_usable_bs >> 2)
		    && *blk != QT_TREEOFF) {
			put_free_dqblk(info, buf, *blk);
			*blk = 0;
		} else {
			ret = write_blk(info, *blk, buf);
			if (ret < 0)
				quota_error(dquot->dq_sb,
					    "Can't write quota tree block %u",
					    *blk);
		}
	}
out_buf:
	kfree(buf);
	return ret;
}