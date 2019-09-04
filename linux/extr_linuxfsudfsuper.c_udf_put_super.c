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
struct udf_sb_info {int /*<<< orphan*/  s_alloc_mutex; int /*<<< orphan*/  s_lvid_bh; int /*<<< orphan*/  s_nls_map; int /*<<< orphan*/  s_vat_inode; } ;
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDF_FLAG_NLS_MAP ; 
 scalar_t__ UDF_QUERY_FLAG (struct super_block*,int /*<<< orphan*/ ) ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  udf_close_lvid (struct super_block*) ; 
 int /*<<< orphan*/  udf_sb_free_partitions (struct super_block*) ; 
 int /*<<< orphan*/  unload_nls (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udf_put_super(struct super_block *sb)
{
	struct udf_sb_info *sbi;

	sbi = UDF_SB(sb);

	iput(sbi->s_vat_inode);
	if (UDF_QUERY_FLAG(sb, UDF_FLAG_NLS_MAP))
		unload_nls(sbi->s_nls_map);
	if (!sb_rdonly(sb))
		udf_close_lvid(sb);
	brelse(sbi->s_lvid_bh);
	udf_sb_free_partitions(sb);
	mutex_destroy(&sbi->s_alloc_mutex);
	kfree(sb->s_fs_info);
	sb->s_fs_info = NULL;
}