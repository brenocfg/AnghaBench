#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct request_sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  icsk_accept_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 scalar_t__ inet_csk_reqsk_queue_add (struct sock*,struct request_sock*,struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reqsk_queue_drop (struct sock*,struct request_sock*) ; 
 int /*<<< orphan*/  reqsk_queue_removed (int /*<<< orphan*/ *,struct request_sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

struct sock *inet_csk_complete_hashdance(struct sock *sk, struct sock *child,
					 struct request_sock *req, bool own_req)
{
	if (own_req) {
		inet_csk_reqsk_queue_drop(sk, req);
		reqsk_queue_removed(&inet_csk(sk)->icsk_accept_queue, req);
		if (inet_csk_reqsk_queue_add(sk, req, child))
			return child;
	}
	/* Too bad, another child took ownership of the request, undo. */
	bh_unlock_sock(child);
	sock_put(child);
	return NULL;
}