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
struct jbd2_buffer_trigger_type {int /*<<< orphan*/  (* t_abort ) (struct jbd2_buffer_trigger_type*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  jh2bh (struct journal_head*) ; 
 int /*<<< orphan*/  stub1 (struct jbd2_buffer_trigger_type*,int /*<<< orphan*/ ) ; 

void jbd2_buffer_abort_trigger(struct journal_head *jh,
			       struct jbd2_buffer_trigger_type *triggers)
{
	if (!triggers || !triggers->t_abort)
		return;

	triggers->t_abort(triggers, jh2bh(jh));
}