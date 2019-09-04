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
struct f2fs_sb_info {int /*<<< orphan*/  nm_info; } ;
struct f2fs_nm_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int f2fs_build_free_nids (struct f2fs_sb_info*,int,int) ; 
 int /*<<< orphan*/  f2fs_kzalloc (struct f2fs_sb_info*,int,int /*<<< orphan*/ ) ; 
 int init_free_nid_cache (struct f2fs_sb_info*) ; 
 int init_node_manager (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  load_free_nid_bitmap (struct f2fs_sb_info*) ; 

int f2fs_build_node_manager(struct f2fs_sb_info *sbi)
{
	int err;

	sbi->nm_info = f2fs_kzalloc(sbi, sizeof(struct f2fs_nm_info),
							GFP_KERNEL);
	if (!sbi->nm_info)
		return -ENOMEM;

	err = init_node_manager(sbi);
	if (err)
		return err;

	err = init_free_nid_cache(sbi);
	if (err)
		return err;

	/* load free nid status from nat_bits table */
	load_free_nid_bitmap(sbi);

	return f2fs_build_free_nids(sbi, true, true);
}