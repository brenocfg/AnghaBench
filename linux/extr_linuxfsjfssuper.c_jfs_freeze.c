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
struct jfs_sb_info {struct jfs_log* log; } ;
struct jfs_log {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_CLEAN ; 
 struct jfs_sb_info* JFS_SBI (struct super_block*) ; 
 int /*<<< orphan*/  jfs_err (char*) ; 
 int /*<<< orphan*/  jfs_error (struct super_block*,char*) ; 
 int lmLogShutdown (struct jfs_log*) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  txQuiesce (struct super_block*) ; 
 int /*<<< orphan*/  txResume (struct super_block*) ; 
 int updateSuper (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jfs_freeze(struct super_block *sb)
{
	struct jfs_sb_info *sbi = JFS_SBI(sb);
	struct jfs_log *log = sbi->log;
	int rc = 0;

	if (!sb_rdonly(sb)) {
		txQuiesce(sb);
		rc = lmLogShutdown(log);
		if (rc) {
			jfs_error(sb, "lmLogShutdown failed\n");

			/* let operations fail rather than hang */
			txResume(sb);

			return rc;
		}
		rc = updateSuper(sb, FM_CLEAN);
		if (rc) {
			jfs_err("jfs_freeze: updateSuper failed");
			/*
			 * Don't fail here. Everything succeeded except
			 * marking the superblock clean, so there's really
			 * no harm in leaving it frozen for now.
			 */
		}
	}
	return 0;
}