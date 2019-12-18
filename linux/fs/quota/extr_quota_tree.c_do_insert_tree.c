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
typedef  int uint ;
struct qtree_mem_dqinfo {int dqi_qtree_depth; int /*<<< orphan*/  dqi_usable_bs; } ;
struct dquot {int /*<<< orphan*/  dq_id; int /*<<< orphan*/  dq_sb; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int find_free_dqentry (struct qtree_mem_dqinfo*,struct dquot*,int*) ; 
 int get_free_dqblk (struct qtree_mem_dqinfo*) ; 
 size_t get_index (struct qtree_mem_dqinfo*,int /*<<< orphan*/ ,int) ; 
 char* getdqbuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_free_dqblk (struct qtree_mem_dqinfo*,char*,int) ; 
 int /*<<< orphan*/  quota_error (int /*<<< orphan*/ ,char*,int) ; 
 int read_blk (struct qtree_mem_dqinfo*,int,char*) ; 
 int write_blk (struct qtree_mem_dqinfo*,int,char*) ; 

__attribute__((used)) static int do_insert_tree(struct qtree_mem_dqinfo *info, struct dquot *dquot,
			  uint *treeblk, int depth)
{
	char *buf = getdqbuf(info->dqi_usable_bs);
	int ret = 0, newson = 0, newact = 0;
	__le32 *ref;
	uint newblk;

	if (!buf)
		return -ENOMEM;
	if (!*treeblk) {
		ret = get_free_dqblk(info);
		if (ret < 0)
			goto out_buf;
		*treeblk = ret;
		memset(buf, 0, info->dqi_usable_bs);
		newact = 1;
	} else {
		ret = read_blk(info, *treeblk, buf);
		if (ret < 0) {
			quota_error(dquot->dq_sb, "Can't read tree quota "
				    "block %u", *treeblk);
			goto out_buf;
		}
	}
	ref = (__le32 *)buf;
	newblk = le32_to_cpu(ref[get_index(info, dquot->dq_id, depth)]);
	if (!newblk)
		newson = 1;
	if (depth == info->dqi_qtree_depth - 1) {
#ifdef __QUOTA_QT_PARANOIA
		if (newblk) {
			quota_error(dquot->dq_sb, "Inserting already present "
				    "quota entry (block %u)",
				    le32_to_cpu(ref[get_index(info,
						dquot->dq_id, depth)]));
			ret = -EIO;
			goto out_buf;
		}
#endif
		newblk = find_free_dqentry(info, dquot, &ret);
	} else {
		ret = do_insert_tree(info, dquot, &newblk, depth+1);
	}
	if (newson && ret >= 0) {
		ref[get_index(info, dquot->dq_id, depth)] =
							cpu_to_le32(newblk);
		ret = write_blk(info, *treeblk, buf);
	} else if (newact && ret < 0) {
		put_free_dqblk(info, buf, *treeblk);
	}
out_buf:
	kfree(buf);
	return ret;
}