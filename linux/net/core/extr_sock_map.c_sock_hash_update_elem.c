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
typedef  int /*<<< orphan*/  u32 ;
struct socket {int /*<<< orphan*/  file; struct sock* sk; } ;
struct sock {scalar_t__ sk_state; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int sock_hash_update_common (struct bpf_map*,void*,struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_map_sk_acquire (struct sock*) ; 
 int /*<<< orphan*/  sock_map_sk_is_suitable (struct sock*) ; 
 int /*<<< orphan*/  sock_map_sk_release (struct sock*) ; 
 struct socket* sockfd_lookup (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int sock_hash_update_elem(struct bpf_map *map, void *key,
				 void *value, u64 flags)
{
	u32 ufd = *(u32 *)value;
	struct socket *sock;
	struct sock *sk;
	int ret;

	sock = sockfd_lookup(ufd, &ret);
	if (!sock)
		return ret;
	sk = sock->sk;
	if (!sk) {
		ret = -EINVAL;
		goto out;
	}
	if (!sock_map_sk_is_suitable(sk) ||
	    sk->sk_state != TCP_ESTABLISHED) {
		ret = -EOPNOTSUPP;
		goto out;
	}

	sock_map_sk_acquire(sk);
	ret = sock_hash_update_common(map, key, sk, flags);
	sock_map_sk_release(sk);
out:
	fput(sock->file);
	return ret;
}