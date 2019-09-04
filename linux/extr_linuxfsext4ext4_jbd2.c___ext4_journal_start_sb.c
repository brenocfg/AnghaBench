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
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/ * s_journal; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ERR_PTR (int) ; 
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/ * ext4_get_nojournal () ; 
 int ext4_journal_check_start (struct super_block*) ; 
 int /*<<< orphan*/ * jbd2__journal_start (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  trace_ext4_journal_start (struct super_block*,int,int,int /*<<< orphan*/ ) ; 

handle_t *__ext4_journal_start_sb(struct super_block *sb, unsigned int line,
				  int type, int blocks, int rsv_blocks)
{
	journal_t *journal;
	int err;

	trace_ext4_journal_start(sb, blocks, rsv_blocks, _RET_IP_);
	err = ext4_journal_check_start(sb);
	if (err < 0)
		return ERR_PTR(err);

	journal = EXT4_SB(sb)->s_journal;
	if (!journal)
		return ext4_get_nojournal();
	return jbd2__journal_start(journal, blocks, rsv_blocks, GFP_NOFS,
				   type, line);
}