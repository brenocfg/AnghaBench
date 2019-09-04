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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct socket {int /*<<< orphan*/  file; TYPE_1__* sk; } ;
struct bpf_sock_ops_kern {TYPE_1__* sk; } ;
struct bpf_map {int dummy; } ;
struct TYPE_3__ {scalar_t__ sk_type; scalar_t__ sk_protocol; scalar_t__ sk_state; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (TYPE_1__*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  release_sock (TYPE_1__*) ; 
 int sock_hash_ctx_update_elem (struct bpf_sock_ops_kern*,struct bpf_map*,void*,int /*<<< orphan*/ ) ; 
 struct socket* sockfd_lookup (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int sock_hash_update_elem(struct bpf_map *map,
				void *key, void *value, u64 flags)
{
	struct bpf_sock_ops_kern skops;
	u32 fd = *(u32 *)value;
	struct socket *socket;
	int err;

	socket = sockfd_lookup(fd, &err);
	if (!socket)
		return err;

	skops.sk = socket->sk;
	if (!skops.sk) {
		fput(socket->file);
		return -EINVAL;
	}

	/* ULPs are currently supported only for TCP sockets in ESTABLISHED
	 * state.
	 */
	if (skops.sk->sk_type != SOCK_STREAM ||
	    skops.sk->sk_protocol != IPPROTO_TCP ||
	    skops.sk->sk_state != TCP_ESTABLISHED) {
		fput(socket->file);
		return -EOPNOTSUPP;
	}

	lock_sock(skops.sk);
	preempt_disable();
	rcu_read_lock();
	err = sock_hash_ctx_update_elem(&skops, map, key, flags);
	rcu_read_unlock();
	preempt_enable();
	release_sock(skops.sk);
	fput(socket->file);
	return err;
}