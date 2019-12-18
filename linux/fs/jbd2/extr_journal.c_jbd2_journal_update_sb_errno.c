#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int j_errno; int /*<<< orphan*/  j_sb_buffer; TYPE_2__* j_superblock; } ;
typedef  TYPE_1__ journal_t ;
struct TYPE_6__ {int /*<<< orphan*/  s_errno; } ;
typedef  TYPE_2__ journal_superblock_t ;

/* Variables and functions */
 int ESHUTDOWN ; 
 int REQ_FUA ; 
 int REQ_SYNC ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  jbd2_write_superblock (TYPE_1__*,int) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,int) ; 
 int /*<<< orphan*/  lock_buffer (int /*<<< orphan*/ ) ; 

void jbd2_journal_update_sb_errno(journal_t *journal)
{
	journal_superblock_t *sb = journal->j_superblock;
	int errcode;

	lock_buffer(journal->j_sb_buffer);
	errcode = journal->j_errno;
	if (errcode == -ESHUTDOWN)
		errcode = 0;
	jbd_debug(1, "JBD2: updating superblock error (errno %d)\n", errcode);
	sb->s_errno    = cpu_to_be32(errcode);

	jbd2_write_superblock(journal, REQ_SYNC | REQ_FUA);
}