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
typedef  int /*<<< orphan*/  u64 ;
struct sock {int dummy; } ;
struct bpf_map {int value_size; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOSPC ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sock* reuseport_array_lookup_elem (struct bpf_map*,void*) ; 
 int /*<<< orphan*/  sock_gen_cookie (struct sock*) ; 

int bpf_fd_reuseport_array_lookup_elem(struct bpf_map *map, void *key,
				       void *value)
{
	struct sock *sk;
	int err;

	if (map->value_size != sizeof(u64))
		return -ENOSPC;

	rcu_read_lock();
	sk = reuseport_array_lookup_elem(map, key);
	if (sk) {
		*(u64 *)value = sock_gen_cookie(sk);
		err = 0;
	} else {
		err = -ENOENT;
	}
	rcu_read_unlock();

	return err;
}