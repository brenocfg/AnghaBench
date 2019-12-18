#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t num; int /*<<< orphan*/ * array; } ;
struct TYPE_5__ {int /*<<< orphan*/  is_leaf; TYPE_3__ children; } ;
typedef  TYPE_1__ obs_hotkey_name_map_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  da_free (TYPE_3__) ; 
 int /*<<< orphan*/  free_edge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_node(obs_hotkey_name_map_node_t *node, bool release)
{
	if (!node->is_leaf) {
		for (size_t i = 0; i < node->children.num; i++)
			free_edge(&node->children.array[i]);

		da_free(node->children);
	}

	if (release && !node->is_leaf)
		bfree(node);
}