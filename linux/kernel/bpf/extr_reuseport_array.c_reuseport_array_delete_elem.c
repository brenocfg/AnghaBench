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
typedef  size_t u32 ;
struct sock {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_user_data; } ;
struct reuseport_array {int /*<<< orphan*/ * ptrs; } ;
struct bpf_map {size_t max_entries; } ;

/* Variables and functions */
 int E2BIG ; 
 int ENOENT ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 struct sock* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct reuseport_array* reuseport_array (struct bpf_map*) ; 
 int /*<<< orphan*/  reuseport_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reuseport_array_delete_elem(struct bpf_map *map, void *key)
{
	struct reuseport_array *array = reuseport_array(map);
	u32 index = *(u32 *)key;
	struct sock *sk;
	int err;

	if (index >= map->max_entries)
		return -E2BIG;

	if (!rcu_access_pointer(array->ptrs[index]))
		return -ENOENT;

	spin_lock_bh(&reuseport_lock);

	sk = rcu_dereference_protected(array->ptrs[index],
				       lockdep_is_held(&reuseport_lock));
	if (sk) {
		write_lock_bh(&sk->sk_callback_lock);
		WRITE_ONCE(sk->sk_user_data, NULL);
		RCU_INIT_POINTER(array->ptrs[index], NULL);
		write_unlock_bh(&sk->sk_callback_lock);
		err = 0;
	} else {
		err = -ENOENT;
	}

	spin_unlock_bh(&reuseport_lock);

	return err;
}