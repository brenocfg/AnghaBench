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
typedef  int uint ;
struct qtree_mem_dqinfo {int dqi_entry_size; int dqi_blocksize_bits; TYPE_1__* dqi_ops; int /*<<< orphan*/  dqi_usable_bs; } ;
struct qt_disk_dqdbheader {int dummy; } ;
struct dquot {int /*<<< orphan*/  dq_id; int /*<<< orphan*/  dq_sb; } ;
typedef  int loff_t ;
struct TYPE_2__ {scalar_t__ (* is_id ) (char*,struct dquot*) ;} ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int from_kqid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* getdqbuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int qtree_dqstr_in_blk (struct qtree_mem_dqinfo*) ; 
 int /*<<< orphan*/  quota_error (int /*<<< orphan*/ ,char*,int) ; 
 int read_blk (struct qtree_mem_dqinfo*,int,char*) ; 
 scalar_t__ stub1 (char*,struct dquot*) ; 

__attribute__((used)) static loff_t find_block_dqentry(struct qtree_mem_dqinfo *info,
				 struct dquot *dquot, uint blk)
{
	char *buf = getdqbuf(info->dqi_usable_bs);
	loff_t ret = 0;
	int i;
	char *ddquot;

	if (!buf)
		return -ENOMEM;
	ret = read_blk(info, blk, buf);
	if (ret < 0) {
		quota_error(dquot->dq_sb, "Can't read quota tree "
			    "block %u", blk);
		goto out_buf;
	}
	ddquot = buf + sizeof(struct qt_disk_dqdbheader);
	for (i = 0; i < qtree_dqstr_in_blk(info); i++) {
		if (info->dqi_ops->is_id(ddquot, dquot))
			break;
		ddquot += info->dqi_entry_size;
	}
	if (i == qtree_dqstr_in_blk(info)) {
		quota_error(dquot->dq_sb,
			    "Quota for id %u referenced but not present",
			    from_kqid(&init_user_ns, dquot->dq_id));
		ret = -EIO;
		goto out_buf;
	} else {
		ret = (blk << info->dqi_blocksize_bits) + sizeof(struct
		  qt_disk_dqdbheader) + i * info->dqi_entry_size;
	}
out_buf:
	kfree(buf);
	return ret;
}