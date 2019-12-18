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
struct sock {int dummy; } ;

/* Variables and functions */
 struct sock* smc_accept_dequeue (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_close_non_accepted (struct sock*) ; 

__attribute__((used)) static void smc_close_cleanup_listen(struct sock *parent)
{
	struct sock *sk;

	/* Close non-accepted connections */
	while ((sk = smc_accept_dequeue(parent, NULL)))
		smc_close_non_accepted(sk);
}