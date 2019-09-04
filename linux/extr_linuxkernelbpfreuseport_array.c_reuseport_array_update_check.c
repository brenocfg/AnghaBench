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
typedef  scalar_t__ u32 ;
struct sock_reuseport {int dummy; } ;
struct sock {scalar_t__ sk_protocol; scalar_t__ sk_family; scalar_t__ sk_type; int /*<<< orphan*/  sk_user_data; } ;
struct reuseport_array {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ BPF_EXIST ; 
 scalar_t__ BPF_NOEXIST ; 
 int EBUSY ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOTSUPP ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_RCU_FREE ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  sk_hashed (struct sock const*) ; 
 int /*<<< orphan*/  sock_flag (struct sock const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
reuseport_array_update_check(const struct reuseport_array *array,
			     const struct sock *nsk,
			     const struct sock *osk,
			     const struct sock_reuseport *nsk_reuse,
			     u32 map_flags)
{
	if (osk && map_flags == BPF_NOEXIST)
		return -EEXIST;

	if (!osk && map_flags == BPF_EXIST)
		return -ENOENT;

	if (nsk->sk_protocol != IPPROTO_UDP && nsk->sk_protocol != IPPROTO_TCP)
		return -ENOTSUPP;

	if (nsk->sk_family != AF_INET && nsk->sk_family != AF_INET6)
		return -ENOTSUPP;

	if (nsk->sk_type != SOCK_STREAM && nsk->sk_type != SOCK_DGRAM)
		return -ENOTSUPP;

	/*
	 * sk must be hashed (i.e. listening in the TCP case or binded
	 * in the UDP case) and
	 * it must also be a SO_REUSEPORT sk (i.e. reuse cannot be NULL).
	 *
	 * Also, sk will be used in bpf helper that is protected by
	 * rcu_read_lock().
	 */
	if (!sock_flag(nsk, SOCK_RCU_FREE) || !sk_hashed(nsk) || !nsk_reuse)
		return -EINVAL;

	/* READ_ONCE because the sk->sk_callback_lock may not be held here */
	if (READ_ONCE(nsk->sk_user_data))
		return -EBUSY;

	return 0;
}