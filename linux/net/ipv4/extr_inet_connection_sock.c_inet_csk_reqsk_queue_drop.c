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
 TYPE_1__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  reqsk_put (struct request_sock*) ; 
 int /*<<< orphan*/  reqsk_queue_removed (int /*<<< orphan*/ *,struct request_sock*) ; 
 scalar_t__ reqsk_queue_unlink (struct request_sock*) ; 

void inet_csk_reqsk_queue_drop(struct sock *sk, struct request_sock *req)
{
	if (reqsk_queue_unlink(req)) {
		reqsk_queue_removed(&inet_csk(sk)->icsk_accept_queue, req);
		reqsk_put(req);
	}
}