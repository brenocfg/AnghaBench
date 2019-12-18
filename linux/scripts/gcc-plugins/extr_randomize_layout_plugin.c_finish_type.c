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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 char* ORIG_TYPE_NAME (scalar_t__) ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_ATTRIBUTES (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 int /*<<< orphan*/  debug_tree (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  randomize_type (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void finish_type(void *event_data, void *data)
{
	tree type = (tree)event_data;

	if (type == NULL_TREE || type == error_mark_node)
		return;

	if (TREE_CODE(type) != RECORD_TYPE)
		return;

	if (TYPE_FIELDS(type) == NULL_TREE)
		return;

	if (lookup_attribute("randomize_considered", TYPE_ATTRIBUTES(type)))
		return;

#ifdef __DEBUG_PLUGIN
	fprintf(stderr, "Calling randomize_type on %s\n", ORIG_TYPE_NAME(type));
#endif
#ifdef __DEBUG_VERBOSE
	debug_tree(type);
#endif
	randomize_type(type);

	return;
}