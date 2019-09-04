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
struct bpf_map {TYPE_1__* ops; int /*<<< orphan*/  usercnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* map_release_uref ) (struct bpf_map*) ;} ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bpf_map*) ; 

__attribute__((used)) static void bpf_map_put_uref(struct bpf_map *map)
{
	if (atomic_dec_and_test(&map->usercnt)) {
		if (map->ops->map_release_uref)
			map->ops->map_release_uref(map);
	}
}