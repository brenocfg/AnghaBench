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
struct super_block {int dummy; } ;
typedef  scalar_t__ sector_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  HFS_NEW_PMAP_MAGIC 129 
#define  HFS_OLD_PMAP_MAGIC 128 
 scalar_t__ HFS_PMAP_BLK ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int hfs_parse_new_pmap (struct super_block*,void*,void*,scalar_t__*,scalar_t__*) ; 
 int hfs_parse_old_pmap (struct super_block*,void*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  hfsplus_min_io_size (struct super_block*) ; 
 int hfsplus_submit_bio (struct super_block*,scalar_t__,void*,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hfs_part_find(struct super_block *sb,
		sector_t *part_start, sector_t *part_size)
{
	void *buf, *data;
	int res;

	buf = kmalloc(hfsplus_min_io_size(sb), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	res = hfsplus_submit_bio(sb, *part_start + HFS_PMAP_BLK,
				 buf, &data, REQ_OP_READ, 0);
	if (res)
		goto out;

	switch (be16_to_cpu(*((__be16 *)data))) {
	case HFS_OLD_PMAP_MAGIC:
		res = hfs_parse_old_pmap(sb, data, part_start, part_size);
		break;
	case HFS_NEW_PMAP_MAGIC:
		res = hfs_parse_new_pmap(sb, buf, data, part_start, part_size);
		break;
	default:
		res = -ENOENT;
		break;
	}
out:
	kfree(buf);
	return res;
}