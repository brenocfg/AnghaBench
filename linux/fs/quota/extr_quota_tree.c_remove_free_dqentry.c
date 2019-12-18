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
typedef  scalar_t__ uint ;
struct qtree_mem_dqinfo {int /*<<< orphan*/  dqi_sb; int /*<<< orphan*/  dqi_type; scalar_t__ dqi_free_entry; int /*<<< orphan*/  dqi_usable_bs; } ;
struct qt_disk_dqdbheader {int /*<<< orphan*/  dqdh_prev_free; int /*<<< orphan*/  dqdh_next_free; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 char* getdqbuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_info_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quota_error (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int read_blk (struct qtree_mem_dqinfo*,scalar_t__,char*) ; 
 int write_blk (struct qtree_mem_dqinfo*,scalar_t__,char*) ; 

__attribute__((used)) static int remove_free_dqentry(struct qtree_mem_dqinfo *info, char *buf,
			       uint blk)
{
	char *tmpbuf = getdqbuf(info->dqi_usable_bs);
	struct qt_disk_dqdbheader *dh = (struct qt_disk_dqdbheader *)buf;
	uint nextblk = le32_to_cpu(dh->dqdh_next_free);
	uint prevblk = le32_to_cpu(dh->dqdh_prev_free);
	int err;

	if (!tmpbuf)
		return -ENOMEM;
	if (nextblk) {
		err = read_blk(info, nextblk, tmpbuf);
		if (err < 0)
			goto out_buf;
		((struct qt_disk_dqdbheader *)tmpbuf)->dqdh_prev_free =
							dh->dqdh_prev_free;
		err = write_blk(info, nextblk, tmpbuf);
		if (err < 0)
			goto out_buf;
	}
	if (prevblk) {
		err = read_blk(info, prevblk, tmpbuf);
		if (err < 0)
			goto out_buf;
		((struct qt_disk_dqdbheader *)tmpbuf)->dqdh_next_free =
							dh->dqdh_next_free;
		err = write_blk(info, prevblk, tmpbuf);
		if (err < 0)
			goto out_buf;
	} else {
		info->dqi_free_entry = nextblk;
		mark_info_dirty(info->dqi_sb, info->dqi_type);
	}
	kfree(tmpbuf);
	dh->dqdh_next_free = dh->dqdh_prev_free = cpu_to_le32(0);
	/* No matter whether write succeeds block is out of list */
	if (write_blk(info, blk, buf) < 0)
		quota_error(info->dqi_sb, "Can't write block (%u) "
			    "with free entries", blk);
	return 0;
out_buf:
	kfree(tmpbuf);
	return err;
}