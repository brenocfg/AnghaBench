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
struct sock {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/ * sk_user_data; } ;
struct reuseport_array {int /*<<< orphan*/ * ptrs; } ;
struct bpf_map {size_t max_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_map_area_free (struct reuseport_array*) ; 
 struct sock* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct reuseport_array* reuseport_array (struct bpf_map*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reuseport_array_free(struct bpf_map *map)
{
	struct reuseport_array *array = reuseport_array(map);
	struct sock *sk;
	u32 i;

	synchronize_rcu();

	/*
	 * ops->map_*_elem() will not be able to access this
	 * array now. Hence, this function only races with
	 * bpf_sk_reuseport_detach() which was triggerred by
	 * close() or disconnect().
	 *
	 * This function and bpf_sk_reuseport_detach() are
	 * both removing sk from "array".  Who removes it
	 * first does not matter.
	 *
	 * The only concern here is bpf_sk_reuseport_detach()
	 * may access "array" which is being freed here.
	 * bpf_sk_reuseport_detach() access this "array"
	 * through sk->sk_user_data _and_ with sk->sk_callback_lock
	 * held which is enough because this "array" is not freed
	 * until all sk->sk_user_data has stopped referencing this "array".
	 *
	 * Hence, due to the above, taking "reuseport_lock" is not
	 * needed here.
	 */

	/*
	 * Since reuseport_lock is not taken, sk is accessed under
	 * rcu_read_lock()
	 */
	rcu_read_lock();
	for (i = 0; i < map->max_entries; i++) {
		sk = rcu_dereference(array->ptrs[i]);
		if (sk) {
			write_lock_bh(&sk->sk_callback_lock);
			/*
			 * No need for WRITE_ONCE(). At this point,
			 * no one is reading it without taking the
			 * sk->sk_callback_lock.
			 */
			sk->sk_user_data = NULL;
			write_unlock_bh(&sk->sk_callback_lock);
			RCU_INIT_POINTER(array->ptrs[i], NULL);
		}
	}
	rcu_read_unlock();

	/*
	 * Once reaching here, all sk->sk_user_data is not
	 * referenceing this "array".  "array" can be freed now.
	 */
	bpf_map_area_free(array);
}