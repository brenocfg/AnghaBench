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
struct squashfs_super_block {int /*<<< orphan*/  bytes_used; int /*<<< orphan*/  s_magic; } ;
struct mtd_info {size_t size; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  sb ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 scalar_t__ SQUASHFS_MAGIC ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 size_t le64_to_cpu (int /*<<< orphan*/ ) ; 
 int mtd_read (struct mtd_info*,size_t,int,size_t*,void*) ; 
 int /*<<< orphan*/  pr_alert (char*,int /*<<< orphan*/ ) ; 

int mtd_get_squashfs_len(struct mtd_info *master,
			 size_t offset,
			 size_t *squashfs_len)
{
	struct squashfs_super_block sb;
	size_t retlen;
	int err;

	err = mtd_read(master, offset, sizeof(sb), &retlen, (void *)&sb);
	if (err || (retlen != sizeof(sb))) {
		pr_alert("error occured while reading from \"%s\"\n",
			 master->name);
		return -EIO;
	}

	if (le32_to_cpu(sb.s_magic) != SQUASHFS_MAGIC) {
		pr_alert("no squashfs found in \"%s\"\n", master->name);
		return -EINVAL;
	}

	retlen = le64_to_cpu(sb.bytes_used);
	if (retlen <= 0) {
		pr_alert("squashfs is empty in \"%s\"\n", master->name);
		return -ENODEV;
	}

	if (offset + retlen > master->size) {
		pr_alert("squashfs has invalid size in \"%s\"\n",
			 master->name);
		return -EINVAL;
	}

	*squashfs_len = retlen;
	return 0;
}