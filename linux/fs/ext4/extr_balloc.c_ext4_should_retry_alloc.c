#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_id; } ;
struct TYPE_3__ {scalar_t__ s_mb_free_pending; int /*<<< orphan*/  s_journal; } ;

/* Variables and functions */
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  ext4_has_free_clusters (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_journal_force_commit_nested (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 

int ext4_should_retry_alloc(struct super_block *sb, int *retries)
{
	if (!ext4_has_free_clusters(EXT4_SB(sb), 1, 0) ||
	    (*retries)++ > 1 ||
	    !EXT4_SB(sb)->s_journal)
		return 0;

	smp_mb();
	if (EXT4_SB(sb)->s_mb_free_pending == 0)
		return 0;

	jbd_debug(1, "%s: retrying operation after ENOSPC\n", sb->s_id);
	jbd2_journal_force_commit_nested(EXT4_SB(sb)->s_journal);
	return 1;
}