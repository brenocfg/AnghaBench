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
typedef  int /*<<< orphan*/  u32 ;
struct bpf_map {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* map_fd_sys_lookup_elem ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  READ_ONCE (void*) ; 
 void** htab_map_lookup_elem (struct bpf_map*,void*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

int bpf_fd_htab_map_lookup_elem(struct bpf_map *map, void *key, u32 *value)
{
	void **ptr;
	int ret = 0;

	if (!map->ops->map_fd_sys_lookup_elem)
		return -ENOTSUPP;

	rcu_read_lock();
	ptr = htab_map_lookup_elem(map, key);
	if (ptr)
		*value = map->ops->map_fd_sys_lookup_elem(READ_ONCE(*ptr));
	else
		ret = -ENOENT;
	rcu_read_unlock();

	return ret;
}