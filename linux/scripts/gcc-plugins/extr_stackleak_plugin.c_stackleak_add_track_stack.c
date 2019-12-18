#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gimple_stmt_iterator ;
typedef  int /*<<< orphan*/  gimple ;
typedef  int /*<<< orphan*/  gcall ;
typedef  int /*<<< orphan*/  cgraph_node_ptr ;
typedef  TYPE_1__* basic_block ;
struct TYPE_4__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSI_CONTINUE_LINKING ; 
 int /*<<< orphan*/  GSI_SAME_STMT ; 
 int /*<<< orphan*/ * as_a_gcall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_create_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cgraph_get_create_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_get_node (int /*<<< orphan*/ ) ; 
 int compute_call_stmt_bb_frequency (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* gimple_bb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gimple_build_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsi_insert_after (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsi_insert_before (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  track_function_decl ; 

__attribute__((used)) static void stackleak_add_track_stack(gimple_stmt_iterator *gsi, bool after)
{
	gimple stmt;
	gcall *stackleak_track_stack;
	cgraph_node_ptr node;
	int frequency;
	basic_block bb;

	/* Insert call to void stackleak_track_stack(void) */
	stmt = gimple_build_call(track_function_decl, 0);
	stackleak_track_stack = as_a_gcall(stmt);
	if (after) {
		gsi_insert_after(gsi, stackleak_track_stack,
						GSI_CONTINUE_LINKING);
	} else {
		gsi_insert_before(gsi, stackleak_track_stack, GSI_SAME_STMT);
	}

	/* Update the cgraph */
	bb = gimple_bb(stackleak_track_stack);
	node = cgraph_get_create_node(track_function_decl);
	gcc_assert(node);
	frequency = compute_call_stmt_bb_frequency(current_function_decl, bb);
	cgraph_create_edge(cgraph_get_node(current_function_decl), node,
			stackleak_track_stack, bb->count, frequency);
}