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
struct qtree_mem_dqinfo {int /*<<< orphan*/  dqi_type; int /*<<< orphan*/  dqi_sb; int /*<<< orphan*/  dqi_free_blk; } ;
struct qt_disk_dqdbheader {int /*<<< orphan*/  dqdh_entries; void* dqdh_prev_free; void* dqdh_next_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_info_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write_blk (struct qtree_mem_dqinfo*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int put_free_dqblk(struct qtree_mem_dqinfo *info, char *buf, uint blk)
{
	struct qt_disk_dqdbheader *dh = (struct qt_disk_dqdbheader *)buf;
	int err;

	dh->dqdh_next_free = cpu_to_le32(info->dqi_free_blk);
	dh->dqdh_prev_free = cpu_to_le32(0);
	dh->dqdh_entries = cpu_to_le16(0);
	err = write_blk(info, blk, buf);
	if (err < 0)
		return err;
	info->dqi_free_blk = blk;
	mark_info_dirty(info->dqi_sb, info->dqi_type);
	return 0;
}