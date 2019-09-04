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
struct journal_head {int dummy; } ;
struct jbd2_buffer_trigger_type {int /*<<< orphan*/  (* t_frozen ) (struct jbd2_buffer_trigger_type*,struct buffer_head*,void*,int /*<<< orphan*/ ) ;} ;
struct buffer_head {int /*<<< orphan*/  b_size; } ;

/* Variables and functions */
 struct buffer_head* jh2bh (struct journal_head*) ; 
 int /*<<< orphan*/  stub1 (struct jbd2_buffer_trigger_type*,struct buffer_head*,void*,int /*<<< orphan*/ ) ; 

void jbd2_buffer_frozen_trigger(struct journal_head *jh, void *mapped_data,
				struct jbd2_buffer_trigger_type *triggers)
{
	struct buffer_head *bh = jh2bh(jh);

	if (!triggers || !triggers->t_frozen)
		return;

	triggers->t_frozen(triggers, bh, mapped_data, bh->b_size);
}