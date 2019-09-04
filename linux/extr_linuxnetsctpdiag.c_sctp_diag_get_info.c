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
struct sock {int /*<<< orphan*/  sk_max_ack_backlog; int /*<<< orphan*/  sk_ack_backlog; } ;
struct sctp_infox {scalar_t__ sctpinfo; TYPE_1__* asoc; } ;
struct inet_diag_msg {int /*<<< orphan*/  idiag_wqueue; int /*<<< orphan*/  idiag_rqueue; } ;
struct TYPE_2__ {int /*<<< orphan*/  sndbuf_used; int /*<<< orphan*/  rmem_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_get_sctp_info (struct sock*,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void sctp_diag_get_info(struct sock *sk, struct inet_diag_msg *r,
			       void *info)
{
	struct sctp_infox *infox = (struct sctp_infox *)info;

	if (infox->asoc) {
		r->idiag_rqueue = atomic_read(&infox->asoc->rmem_alloc);
		r->idiag_wqueue = infox->asoc->sndbuf_used;
	} else {
		r->idiag_rqueue = sk->sk_ack_backlog;
		r->idiag_wqueue = sk->sk_max_ack_backlog;
	}
	if (infox->sctpinfo)
		sctp_get_sctp_info(sk, infox->asoc, infox->sctpinfo);
}