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
struct sock {int /*<<< orphan*/ * sk_destruct; } ;

/* Variables and functions */
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_free (struct sock*) ; 

void sk_free_unlock_clone(struct sock *sk)
{
	/* It is still raw copy of parent, so invalidate
	 * destructor and make plain sk_free() */
	sk->sk_destruct = NULL;
	bh_unlock_sock(sk);
	sk_free(sk);
}