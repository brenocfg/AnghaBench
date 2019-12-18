#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int target_varno; int sublevels_up; int map_length; int* found_whole_row; int /*<<< orphan*/  to_rowtype; int /*<<< orphan*/  const* attno_map; } ;
typedef  TYPE_1__ map_variable_attnos_context ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  map_variable_attnos_mutator ; 
 int /*<<< orphan*/ * query_or_expression_tree_mutator (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

Node *
map_variable_attnos(Node *node,
					int target_varno, int sublevels_up,
					const AttrNumber *attno_map, int map_length,
					Oid to_rowtype, bool *found_whole_row)
{
	map_variable_attnos_context context;

	context.target_varno = target_varno;
	context.sublevels_up = sublevels_up;
	context.attno_map = attno_map;
	context.map_length = map_length;
	context.to_rowtype = to_rowtype;
	context.found_whole_row = found_whole_row;

	*found_whole_row = false;

	/*
	 * Must be prepared to start with a Query or a bare expression tree; if
	 * it's a Query, we don't want to increment sublevels_up.
	 */
	return query_or_expression_tree_mutator(node,
											map_variable_attnos_mutator,
											(void *) &context,
											0);
}