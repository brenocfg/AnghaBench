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
struct sock {int sk_err; } ;
struct TYPE_2__ {struct sock* sk; } ;
struct sctp_association {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDP ; 
 int /*<<< orphan*/  sctp_style (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sctp_cmd_set_sk_err(struct sctp_association *asoc, int error)
{
	struct sock *sk = asoc->base.sk;

	if (!sctp_style(sk, UDP))
		sk->sk_err = error;
}