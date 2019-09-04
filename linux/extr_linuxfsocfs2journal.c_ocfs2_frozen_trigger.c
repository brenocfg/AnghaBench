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
struct ocfs2_triggers {int ot_offset; } ;
struct jbd2_buffer_trigger_type {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_block_check_compute (void*,size_t,void*) ; 
 struct ocfs2_triggers* to_ocfs2_trigger (struct jbd2_buffer_trigger_type*) ; 

__attribute__((used)) static void ocfs2_frozen_trigger(struct jbd2_buffer_trigger_type *triggers,
				 struct buffer_head *bh,
				 void *data, size_t size)
{
	struct ocfs2_triggers *ot = to_ocfs2_trigger(triggers);

	/*
	 * We aren't guaranteed to have the superblock here, so we
	 * must unconditionally compute the ecc data.
	 * __ocfs2_journal_access() will only set the triggers if
	 * metaecc is enabled.
	 */
	ocfs2_block_check_compute(data, size, data + ot->ot_offset);
}