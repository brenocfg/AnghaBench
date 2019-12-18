#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct super_block {int dummy; } ;
struct hfs_find_data {int /*<<< orphan*/  search_key; } ;
struct TYPE_7__ {int /*<<< orphan*/  length; } ;
struct TYPE_5__ {TYPE_3__ nodeName; int /*<<< orphan*/  parentID; } ;
struct TYPE_6__ {TYPE_1__ thread; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ hfsplus_cat_entry ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ HFSPLUS_FILE_THREAD ; 
 scalar_t__ HFSPLUS_FOLDER_THREAD ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int hfs_brec_find (struct hfs_find_data*,int /*<<< orphan*/ ) ; 
 int hfs_brec_read (struct hfs_find_data*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  hfs_find_rec_by_key ; 
 int /*<<< orphan*/  hfsplus_cat_build_key_uni (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  hfsplus_cat_build_key_with_cnid (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int hfsplus_find_cat(struct super_block *sb, u32 cnid,
		     struct hfs_find_data *fd)
{
	hfsplus_cat_entry tmp;
	int err;
	u16 type;

	hfsplus_cat_build_key_with_cnid(sb, fd->search_key, cnid);
	err = hfs_brec_read(fd, &tmp, sizeof(hfsplus_cat_entry));
	if (err)
		return err;

	type = be16_to_cpu(tmp.type);
	if (type != HFSPLUS_FOLDER_THREAD && type != HFSPLUS_FILE_THREAD) {
		pr_err("found bad thread record in catalog\n");
		return -EIO;
	}

	if (be16_to_cpu(tmp.thread.nodeName.length) > 255) {
		pr_err("catalog name length corrupted\n");
		return -EIO;
	}

	hfsplus_cat_build_key_uni(fd->search_key,
		be32_to_cpu(tmp.thread.parentID),
		&tmp.thread.nodeName);
	return hfs_brec_find(fd, hfs_find_rec_by_key);
}