#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {struct sock* private; } ;
struct unix_sock {TYPE_1__ peer_wait; TYPE_2__ peer_wake; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __add_wait_queue (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct unix_sock* unix_sk (struct sock*) ; 

__attribute__((used)) static int unix_dgram_peer_wake_connect(struct sock *sk, struct sock *other)
{
	struct unix_sock *u, *u_other;
	int rc;

	u = unix_sk(sk);
	u_other = unix_sk(other);
	rc = 0;
	spin_lock(&u_other->peer_wait.lock);

	if (!u->peer_wake.private) {
		u->peer_wake.private = other;
		__add_wait_queue(&u_other->peer_wait, &u->peer_wake);

		rc = 1;
	}

	spin_unlock(&u_other->peer_wait.lock);
	return rc;
}