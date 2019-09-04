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
struct crush_choose_arg_map {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 struct crush_choose_arg_map* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct crush_choose_arg_map *alloc_choose_arg_map(void)
{
	struct crush_choose_arg_map *arg_map;

	arg_map = kzalloc(sizeof(*arg_map), GFP_NOIO);
	if (!arg_map)
		return NULL;

	RB_CLEAR_NODE(&arg_map->node);
	return arg_map;
}