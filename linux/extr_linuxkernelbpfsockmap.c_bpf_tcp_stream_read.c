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
struct sock {int dummy; } ;
struct smap_psock {int /*<<< orphan*/  ingress; } ;

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct smap_psock* smap_psock_sk (struct sock const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool bpf_tcp_stream_read(const struct sock *sk)
{
	struct smap_psock *psock;
	bool empty = true;

	rcu_read_lock();
	psock = smap_psock_sk(sk);
	if (unlikely(!psock))
		goto out;
	empty = list_empty(&psock->ingress);
out:
	rcu_read_unlock();
	return !empty;
}