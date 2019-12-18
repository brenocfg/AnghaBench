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
struct buffer_head {int dummy; } ;
struct blk_plug {int dummy; } ;
struct TYPE_3__ {struct buffer_head** j_chkpt_bhs; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int /*<<< orphan*/  REQ_SYNC ; 
 int /*<<< orphan*/  __brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  write_dirty_buffer (struct buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__flush_batch(journal_t *journal, int *batch_count)
{
	int i;
	struct blk_plug plug;

	blk_start_plug(&plug);
	for (i = 0; i < *batch_count; i++)
		write_dirty_buffer(journal->j_chkpt_bhs[i], REQ_SYNC);
	blk_finish_plug(&plug);

	for (i = 0; i < *batch_count; i++) {
		struct buffer_head *bh = journal->j_chkpt_bhs[i];
		BUFFER_TRACE(bh, "brelse");
		__brelse(bh);
	}
	*batch_count = 0;
}