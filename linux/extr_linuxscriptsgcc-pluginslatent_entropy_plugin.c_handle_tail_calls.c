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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  gimple_stmt_iterator ;
typedef  int /*<<< orphan*/  gimple ;
typedef  int /*<<< orphan*/  gcall ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  __perturb_latent_entropy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * as_a_gcall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimple_call_tail_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gsi_start_bb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gimple_call (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool handle_tail_calls(basic_block bb, tree local_entropy)
{
	gimple_stmt_iterator gsi;

	for (gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi)) {
		gcall *call;
		gimple stmt = gsi_stmt(gsi);

		if (!is_gimple_call(stmt))
			continue;

		call = as_a_gcall(stmt);
		if (!gimple_call_tail_p(call))
			continue;

		__perturb_latent_entropy(&gsi, local_entropy);
		return true;
	}

	return false;
}