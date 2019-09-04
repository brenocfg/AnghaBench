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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNIX_DIAG_PEER ; 
 int nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int sock_i_ino (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 struct sock* unix_peer_get (struct sock*) ; 
 int /*<<< orphan*/  unix_state_lock (struct sock*) ; 
 int /*<<< orphan*/  unix_state_unlock (struct sock*) ; 

__attribute__((used)) static int sk_diag_dump_peer(struct sock *sk, struct sk_buff *nlskb)
{
	struct sock *peer;
	int ino;

	peer = unix_peer_get(sk);
	if (peer) {
		unix_state_lock(peer);
		ino = sock_i_ino(peer);
		unix_state_unlock(peer);
		sock_put(peer);

		return nla_put_u32(nlskb, UNIX_DIAG_PEER, ino);
	}

	return 0;
}