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
typedef  int /*<<< orphan*/  obs_hotkey_name_map_node_t ;

/* Variables and functions */
 int /*<<< orphan*/ * bzalloc (int) ; 

__attribute__((used)) static inline obs_hotkey_name_map_node_t *new_node(void)
{
	return bzalloc(sizeof(obs_hotkey_name_map_node_t));
}