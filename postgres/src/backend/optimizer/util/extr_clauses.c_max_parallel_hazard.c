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
struct TYPE_3__ {char max_hazard; int /*<<< orphan*/  safe_param_ids; int /*<<< orphan*/  max_interesting; } ;
typedef  TYPE_1__ max_parallel_hazard_context ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  NIL ; 
 char PROPARALLEL_SAFE ; 
 int /*<<< orphan*/  PROPARALLEL_UNSAFE ; 
 int /*<<< orphan*/  max_parallel_hazard_walker (int /*<<< orphan*/ *,TYPE_1__*) ; 

char
max_parallel_hazard(Query *parse)
{
	max_parallel_hazard_context context;

	context.max_hazard = PROPARALLEL_SAFE;
	context.max_interesting = PROPARALLEL_UNSAFE;
	context.safe_param_ids = NIL;
	(void) max_parallel_hazard_walker((Node *) parse, &context);
	return context.max_hazard;
}