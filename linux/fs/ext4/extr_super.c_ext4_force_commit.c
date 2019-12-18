#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_2__ {int /*<<< orphan*/ * s_journal; } ;

/* Variables and functions */
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 int ext4_journal_force_commit (int /*<<< orphan*/ *) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 

int ext4_force_commit(struct super_block *sb)
{
	journal_t *journal;

	if (sb_rdonly(sb))
		return 0;

	journal = EXT4_SB(sb)->s_journal;
	return ext4_journal_force_commit(journal);
}