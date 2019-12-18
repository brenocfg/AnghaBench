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
struct sock {scalar_t__ sk_shutdown; } ;
struct sctp_cmd_seq {int dummy; } ;
struct TYPE_2__ {struct sock* sk; } ;
struct sctp_association {int /*<<< orphan*/  temp; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  LISTENING ; 
 scalar_t__ SHUTDOWN_MASK ; 
 int /*<<< orphan*/  TCP ; 
 int /*<<< orphan*/  sctp_association_free (struct sctp_association*) ; 
 scalar_t__ sctp_sstate (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_style (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sctp_cmd_delete_tcb(struct sctp_cmd_seq *cmds,
				struct sctp_association *asoc)
{
	struct sock *sk = asoc->base.sk;

	/* If it is a non-temporary association belonging to a TCP-style
	 * listening socket that is not closed, do not free it so that accept()
	 * can pick it up later.
	 */
	if (sctp_style(sk, TCP) && sctp_sstate(sk, LISTENING) &&
	    (!asoc->temp) && (sk->sk_shutdown != SHUTDOWN_MASK))
		return;

	sctp_association_free(asoc);
}