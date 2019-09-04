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
typedef  int /*<<< orphan*/  obs_hotkey_name_map_node_t ;
struct TYPE_3__ {int /*<<< orphan*/ * node; } ;
typedef  TYPE_1__ obs_hotkey_name_map_edge_t ;

/* Variables and functions */

__attribute__((used)) static void connect(obs_hotkey_name_map_edge_t *e,
		obs_hotkey_name_map_node_t *n)
{
	e->node = n;
}