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
struct erofs_sb_info {int /*<<< orphan*/ * managed_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 struct erofs_sb_info* EROFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  erofs_shrinker_unregister (struct super_block*) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void erofs_put_super(struct super_block *sb)
{
	struct erofs_sb_info *const sbi = EROFS_SB(sb);

	DBG_BUGON(!sbi);

	erofs_shrinker_unregister(sb);
#ifdef CONFIG_EROFS_FS_ZIP
	iput(sbi->managed_cache);
	sbi->managed_cache = NULL;
#endif
}