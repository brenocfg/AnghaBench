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
struct sock {int sk_err; int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;int /*<<< orphan*/  sk_shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHUTDOWN_MASK ; 
 int /*<<< orphan*/  pr_debug (char*,struct sock*,int) ; 
 int /*<<< orphan*/  rawsock_write_queue_purge (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void rawsock_report_error(struct sock *sk, int err)
{
	pr_debug("sk=%p err=%d\n", sk, err);

	sk->sk_shutdown = SHUTDOWN_MASK;
	sk->sk_err = -err;
	sk->sk_error_report(sk);

	rawsock_write_queue_purge(sk);
}