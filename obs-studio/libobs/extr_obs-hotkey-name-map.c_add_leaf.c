#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  children; } ;
typedef  TYPE_1__ obs_hotkey_name_map_node_t ;
struct TYPE_9__ {TYPE_4__* node; } ;
typedef  TYPE_2__ obs_hotkey_name_map_edge_t ;
struct TYPE_10__ {int val; } ;

/* Variables and functions */
 TYPE_2__* da_push_back_new (int /*<<< orphan*/ ) ; 
 TYPE_4__* new_leaf () ; 
 int /*<<< orphan*/  set_prefix (TYPE_2__*,char const*,size_t) ; 

__attribute__((used)) static obs_hotkey_name_map_edge_t *add_leaf(obs_hotkey_name_map_node_t *node,
					    const char *key, size_t l, int v)
{
	obs_hotkey_name_map_edge_t *e = da_push_back_new(node->children);

	set_prefix(e, key, l);

	e->node = new_leaf();
	e->node->val = v;

	return e;
}