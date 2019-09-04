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
struct qtree_mem_dqinfo {int dqi_usable_bs; int dqi_qtree_depth; int /*<<< orphan*/  dqi_sb; } ;
typedef  int ssize_t ;
typedef  unsigned int qid_t ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int __get_index (struct qtree_mem_dqinfo*,unsigned int,int) ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 char* getdqbuf (int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 unsigned int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  quota_error (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int read_blk (struct qtree_mem_dqinfo*,unsigned int,char*) ; 

__attribute__((used)) static int find_next_id(struct qtree_mem_dqinfo *info, qid_t *id,
			unsigned int blk, int depth)
{
	char *buf = getdqbuf(info->dqi_usable_bs);
	__le32 *ref = (__le32 *)buf;
	ssize_t ret;
	unsigned int epb = info->dqi_usable_bs >> 2;
	unsigned int level_inc = 1;
	int i;

	if (!buf)
		return -ENOMEM;

	for (i = depth; i < info->dqi_qtree_depth - 1; i++)
		level_inc *= epb;

	ret = read_blk(info, blk, buf);
	if (ret < 0) {
		quota_error(info->dqi_sb,
			    "Can't read quota tree block %u", blk);
		goto out_buf;
	}
	for (i = __get_index(info, *id, depth); i < epb; i++) {
		if (ref[i] == cpu_to_le32(0)) {
			*id += level_inc;
			continue;
		}
		if (depth == info->dqi_qtree_depth - 1) {
			ret = 0;
			goto out_buf;
		}
		ret = find_next_id(info, id, le32_to_cpu(ref[i]), depth + 1);
		if (ret != -ENOENT)
			break;
	}
	if (i == epb) {
		ret = -ENOENT;
		goto out_buf;
	}
out_buf:
	kfree(buf);
	return ret;
}