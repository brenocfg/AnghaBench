#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t next_leaf; TYPE_3__* leaves; } ;
typedef  TYPE_2__ obs_hotkey_name_map_t ;
struct TYPE_8__ {int is_leaf; } ;
typedef  TYPE_3__ obs_hotkey_name_map_node_t ;
struct TYPE_6__ {TYPE_2__* name_map; } ;
struct TYPE_9__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 TYPE_4__* obs ; 

__attribute__((used)) static inline obs_hotkey_name_map_node_t *new_leaf(void)
{
	obs_hotkey_name_map_t *name_map = obs->hotkeys.name_map;
	obs_hotkey_name_map_node_t *node =
		&name_map->leaves[name_map->next_leaf];
	name_map->next_leaf += 1;

	node->is_leaf = true;
	return node;
}