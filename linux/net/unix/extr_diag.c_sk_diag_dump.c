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
typedef  int /*<<< orphan*/  u32 ;
struct unix_diag_req {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int sk_diag_fill (struct sock*,struct sk_buff*,struct unix_diag_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sock_i_ino (struct sock*) ; 
 int /*<<< orphan*/  unix_state_lock (struct sock*) ; 
 int /*<<< orphan*/  unix_state_unlock (struct sock*) ; 

__attribute__((used)) static int sk_diag_dump(struct sock *sk, struct sk_buff *skb, struct unix_diag_req *req,
		u32 portid, u32 seq, u32 flags)
{
	int sk_ino;

	unix_state_lock(sk);
	sk_ino = sock_i_ino(sk);
	unix_state_unlock(sk);

	if (!sk_ino)
		return 0;

	return sk_diag_fill(sk, skb, req, portid, seq, flags, sk_ino);
}