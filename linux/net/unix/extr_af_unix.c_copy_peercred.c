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
struct sock {scalar_t__ sk_peer_cred; int /*<<< orphan*/  sk_peer_pid; } ;

/* Variables and functions */
 scalar_t__ get_cred (scalar_t__) ; 
 int /*<<< orphan*/  get_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cred (scalar_t__) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_peercred(struct sock *sk, struct sock *peersk)
{
	put_pid(sk->sk_peer_pid);
	if (sk->sk_peer_cred)
		put_cred(sk->sk_peer_cred);
	sk->sk_peer_pid  = get_pid(peersk->sk_peer_pid);
	sk->sk_peer_cred = get_cred(peersk->sk_peer_cred);
}