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
struct sock {int /*<<< orphan*/  sk_ack_backlog; } ;
struct TYPE_2__ {struct sock* sk; } ;
struct sctp_endpoint {int /*<<< orphan*/  asocs; TYPE_1__ base; } ;
struct sctp_association {int /*<<< orphan*/  asocs; scalar_t__ temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LISTENING ; 
 int /*<<< orphan*/  TCP ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sctp_sstate (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_style (struct sock*,int /*<<< orphan*/ ) ; 

void sctp_endpoint_add_asoc(struct sctp_endpoint *ep,
			    struct sctp_association *asoc)
{
	struct sock *sk = ep->base.sk;

	/* If this is a temporary association, don't bother
	 * since we'll be removing it shortly and don't
	 * want anyone to find it anyway.
	 */
	if (asoc->temp)
		return;

	/* Now just add it to our list of asocs */
	list_add_tail(&asoc->asocs, &ep->asocs);

	/* Increment the backlog value for a TCP-style listening socket. */
	if (sctp_style(sk, TCP) && sctp_sstate(sk, LISTENING))
		sk->sk_ack_backlog++;
}