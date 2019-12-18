#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ prefix_len; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ obs_hotkey_name_map_edge_t ;

/* Variables and functions */
 scalar_t__ NAME_MAP_COMPRESS_LENGTH ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_node (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_prefix (TYPE_1__*) ; 

__attribute__((used)) static void free_edge(obs_hotkey_name_map_edge_t *edge)
{
	free_node(edge->node, true);

	if (edge->prefix_len < NAME_MAP_COMPRESS_LENGTH)
		return;

	bfree(get_prefix(edge));
}