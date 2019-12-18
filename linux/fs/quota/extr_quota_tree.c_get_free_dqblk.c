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
struct qtree_mem_dqinfo {int dqi_free_blk; int /*<<< orphan*/  dqi_type; int /*<<< orphan*/  dqi_sb; int /*<<< orphan*/  dqi_blocks; int /*<<< orphan*/  dqi_usable_bs; } ;
struct qt_disk_dqdbheader {int /*<<< orphan*/  dqdh_next_free; } ;

/* Variables and functions */
 int ENOMEM ; 
 char* getdqbuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_info_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_blk (struct qtree_mem_dqinfo*,int,char*) ; 
 int write_blk (struct qtree_mem_dqinfo*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int get_free_dqblk(struct qtree_mem_dqinfo *info)
{
	char *buf = getdqbuf(info->dqi_usable_bs);
	struct qt_disk_dqdbheader *dh = (struct qt_disk_dqdbheader *)buf;
	int ret, blk;

	if (!buf)
		return -ENOMEM;
	if (info->dqi_free_blk) {
		blk = info->dqi_free_blk;
		ret = read_blk(info, blk, buf);
		if (ret < 0)
			goto out_buf;
		info->dqi_free_blk = le32_to_cpu(dh->dqdh_next_free);
	}
	else {
		memset(buf, 0, info->dqi_usable_bs);
		/* Assure block allocation... */
		ret = write_blk(info, info->dqi_blocks, buf);
		if (ret < 0)
			goto out_buf;
		blk = info->dqi_blocks++;
	}
	mark_info_dirty(info->dqi_sb, info->dqi_type);
	ret = blk;
out_buf:
	kfree(buf);
	return ret;
}