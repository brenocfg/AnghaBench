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
struct super_block {scalar_t__ s_magic; int /*<<< orphan*/ * s_fs_info; } ;
struct erofs_sb_info {int /*<<< orphan*/  umount_mutex; int /*<<< orphan*/  dev_name; } ;

/* Variables and functions */
 struct erofs_sb_info* EROFS_SB (struct super_block*) ; 
 scalar_t__ EROFS_SUPER_MAGIC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __putname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  erofs_unregister_super (struct super_block*) ; 
 int /*<<< orphan*/  infoln (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct erofs_sb_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void erofs_put_super(struct super_block *sb)
{
	struct erofs_sb_info *sbi = EROFS_SB(sb);

	/* for cases which are failed in "read_super" */
	if (sbi == NULL)
		return;

	WARN_ON(sb->s_magic != EROFS_SUPER_MAGIC);

	infoln("unmounted for %s", sbi->dev_name);
	__putname(sbi->dev_name);

#ifdef EROFS_FS_HAS_MANAGED_CACHE
	iput(sbi->managed_cache);
#endif

	mutex_lock(&sbi->umount_mutex);

#ifdef CONFIG_EROFS_FS_ZIP
	erofs_workstation_cleanup_all(sb);
#endif

	erofs_unregister_super(sb);
	mutex_unlock(&sbi->umount_mutex);

	kfree(sbi);
	sb->s_fs_info = NULL;
}