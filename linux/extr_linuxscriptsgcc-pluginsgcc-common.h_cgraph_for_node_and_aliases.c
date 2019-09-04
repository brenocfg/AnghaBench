#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* cgraph_node_ptr ;
struct TYPE_6__ {struct TYPE_6__* next; struct TYPE_6__* same_body; } ;

/* Variables and functions */
 scalar_t__ AVAIL_OVERWRITABLE ; 
 scalar_t__ cgraph_function_body_availability (TYPE_1__*) ; 

__attribute__((used)) static inline bool cgraph_for_node_and_aliases(cgraph_node_ptr node, bool (*callback)(cgraph_node_ptr, void *), void *data, bool include_overwritable)
{
	cgraph_node_ptr alias;

	if (callback(node, data))
		return true;

	for (alias = node->same_body; alias; alias = alias->next) {
		if (include_overwritable || cgraph_function_body_availability(alias) > AVAIL_OVERWRITABLE)
			if (cgraph_for_node_and_aliases(alias, callback, data, include_overwritable))
				return true;
	}

	return false;
}