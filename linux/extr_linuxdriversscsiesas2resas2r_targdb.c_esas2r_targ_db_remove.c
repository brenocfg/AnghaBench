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
struct esas2r_target {int /*<<< orphan*/  target_state; } ;
struct esas2r_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TS_NOT_PRESENT ; 
 int /*<<< orphan*/  esas2r_targ_get_id (struct esas2r_target*,struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_trace_enter () ; 
 int /*<<< orphan*/  esas2r_trace_exit () ; 

void esas2r_targ_db_remove(struct esas2r_adapter *a, struct esas2r_target *t)
{
	esas2r_trace_enter();

	t->target_state = TS_NOT_PRESENT;

	esas2r_trace("remove id:%d", esas2r_targ_get_id(t, a));

	esas2r_trace_exit();
}