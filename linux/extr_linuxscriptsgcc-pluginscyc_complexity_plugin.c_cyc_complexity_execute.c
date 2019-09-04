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
struct TYPE_3__ {char* file; } ;
typedef  TYPE_1__ expanded_location ;

/* Variables and functions */
 char* DECL_NAME_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_SOURCE_LOCATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfun ; 
 int /*<<< orphan*/  current_function_decl ; 
 TYPE_1__ expand_location (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*,char*) ; 
 int n_basic_blocks_for_fn (int /*<<< orphan*/ ) ; 
 int n_edges_for_fn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static unsigned int cyc_complexity_execute(void)
{
	int complexity;
	expanded_location xloc;

	/* M = E - N + 2P */
	complexity = n_edges_for_fn(cfun) - n_basic_blocks_for_fn(cfun) + 2;

	xloc = expand_location(DECL_SOURCE_LOCATION(current_function_decl));
	fprintf(stderr, "Cyclomatic Complexity %d %s:%s\n", complexity,
		xloc.file, DECL_NAME_POINTER(current_function_decl));

	return 0;
}