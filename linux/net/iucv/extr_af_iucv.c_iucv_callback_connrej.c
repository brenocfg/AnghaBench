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
typedef  int /*<<< orphan*/  u8 ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;} ;
struct iucv_path {struct sock* private; } ;

/* Variables and functions */
 scalar_t__ IUCV_CLOSED ; 
 scalar_t__ IUCV_DISCONN ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  iucv_sever_path (struct sock*,int) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void iucv_callback_connrej(struct iucv_path *path, u8 ipuser[16])
{
	struct sock *sk = path->private;

	if (sk->sk_state == IUCV_CLOSED)
		return;

	bh_lock_sock(sk);
	iucv_sever_path(sk, 1);
	sk->sk_state = IUCV_DISCONN;

	sk->sk_state_change(sk);
	bh_unlock_sock(sk);
}