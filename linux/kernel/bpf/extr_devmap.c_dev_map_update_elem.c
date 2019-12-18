#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct bpf_map {int dummy; } ;
struct TYPE_4__ {TYPE_1__* nsproxy; } ;
struct TYPE_3__ {int /*<<< orphan*/  net_ns; } ;

/* Variables and functions */
 int __dev_map_update_elem (int /*<<< orphan*/ ,struct bpf_map*,void*,void*,int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 

__attribute__((used)) static int dev_map_update_elem(struct bpf_map *map, void *key, void *value,
			       u64 map_flags)
{
	return __dev_map_update_elem(current->nsproxy->net_ns,
				     map, key, value, map_flags);
}