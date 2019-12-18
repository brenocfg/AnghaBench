#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  h_buffer_credits; TYPE_1__* h_journal; } ;
typedef  TYPE_2__ handle_t ;
struct TYPE_10__ {struct super_block* j_private; } ;

/* Variables and functions */
 TYPE_2__* ERR_PTR (int) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 TYPE_2__* ext4_get_nojournal () ; 
 int /*<<< orphan*/  ext4_handle_valid (TYPE_2__*) ; 
 int ext4_journal_check_start (struct super_block*) ; 
 int /*<<< orphan*/  jbd2_journal_free_reserved (TYPE_2__*) ; 
 int jbd2_journal_start_reserved (TYPE_2__*,int,unsigned int) ; 
 int /*<<< orphan*/  trace_ext4_journal_start_reserved (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

handle_t *__ext4_journal_start_reserved(handle_t *handle, unsigned int line,
					int type)
{
	struct super_block *sb;
	int err;

	if (!ext4_handle_valid(handle))
		return ext4_get_nojournal();

	sb = handle->h_journal->j_private;
	trace_ext4_journal_start_reserved(sb, handle->h_buffer_credits,
					  _RET_IP_);
	err = ext4_journal_check_start(sb);
	if (err < 0) {
		jbd2_journal_free_reserved(handle);
		return ERR_PTR(err);
	}

	err = jbd2_journal_start_reserved(handle, type, line);
	if (err < 0)
		return ERR_PTR(err);
	return handle;
}