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
struct crush_choose_arg_map {int /*<<< orphan*/ * args; } ;
struct ceph_osdmap {int /*<<< orphan*/  crush_workspace_mutex; int /*<<< orphan*/  crush_workspace; TYPE_1__* crush; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  choose_args; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CEPH_DEFAULT_CHOOSE_ARGS ; 
 int CEPH_PG_MAX_SIZE ; 
 int crush_do_rule (TYPE_1__*,int,int,int*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct crush_choose_arg_map* lookup_choose_arg_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_crush(struct ceph_osdmap *map, int ruleno, int x,
		    int *result, int result_max,
		    const __u32 *weight, int weight_max,
		    s64 choose_args_index)
{
	struct crush_choose_arg_map *arg_map;
	int r;

	BUG_ON(result_max > CEPH_PG_MAX_SIZE);

	arg_map = lookup_choose_arg_map(&map->crush->choose_args,
					choose_args_index);
	if (!arg_map)
		arg_map = lookup_choose_arg_map(&map->crush->choose_args,
						CEPH_DEFAULT_CHOOSE_ARGS);

	mutex_lock(&map->crush_workspace_mutex);
	r = crush_do_rule(map->crush, ruleno, x, result, result_max,
			  weight, weight_max, map->crush_workspace,
			  arg_map ? arg_map->args : NULL);
	mutex_unlock(&map->crush_workspace_mutex);

	return r;
}