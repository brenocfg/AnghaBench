#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_refcnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  inet_num; } ;

/* Variables and functions */
 TYPE_1__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  pr_debug (char*,TYPE_1__*,...) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_common_release (struct sock*) ; 

void ping_close(struct sock *sk, long timeout)
{
	pr_debug("ping_close(sk=%p,sk->num=%u)\n",
		 inet_sk(sk), inet_sk(sk)->inet_num);
	pr_debug("isk->refcnt = %d\n", refcount_read(&sk->sk_refcnt));

	sk_common_release(sk);
}