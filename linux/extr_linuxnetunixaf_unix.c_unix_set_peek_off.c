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
struct unix_sock {int /*<<< orphan*/  iolock; } ;
struct sock {int sk_peek_off; } ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct unix_sock* unix_sk (struct sock*) ; 

__attribute__((used)) static int unix_set_peek_off(struct sock *sk, int val)
{
	struct unix_sock *u = unix_sk(sk);

	if (mutex_lock_interruptible(&u->iolock))
		return -EINTR;

	sk->sk_peek_off = val;
	mutex_unlock(&u->iolock);

	return 0;
}