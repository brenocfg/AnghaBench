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
struct tcp_ulp_ops {int (* init ) (struct sock*) ;int /*<<< orphan*/  owner; } ;
struct sock {int dummy; } ;
struct inet_connection_sock {struct tcp_ulp_ops const* icsk_ulp_ops; } ;

/* Variables and functions */
 int EEXIST ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int stub1 (struct sock*) ; 

__attribute__((used)) static int __tcp_set_ulp(struct sock *sk, const struct tcp_ulp_ops *ulp_ops)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	int err;

	err = -EEXIST;
	if (icsk->icsk_ulp_ops)
		goto out_err;

	err = ulp_ops->init(sk);
	if (err)
		goto out_err;

	icsk->icsk_ulp_ops = ulp_ops;
	return 0;
out_err:
	module_put(ulp_ops->owner);
	return err;
}