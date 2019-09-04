#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct TYPE_6__ {scalar_t__ dead; } ;
struct sctp_association {int /*<<< orphan*/  asocs; TYPE_2__ base; TYPE_1__* ep; } ;
struct TYPE_8__ {TYPE_3__* ep; } ;
struct TYPE_7__ {int /*<<< orphan*/  asocs; } ;
struct TYPE_5__ {scalar_t__ sndbuf_policy; } ;

/* Variables and functions */
 void __sctp_write_space (struct sctp_association*) ; 
 int /*<<< orphan*/  asocs ; 
 struct sctp_association* list_next_entry (struct sctp_association*,int /*<<< orphan*/ ) ; 
 TYPE_4__* sctp_sk (struct sock*) ; 
 void sctp_write_space (struct sock*) ; 

__attribute__((used)) static void sctp_wake_up_waiters(struct sock *sk,
				 struct sctp_association *asoc)
{
	struct sctp_association *tmp = asoc;

	/* We do accounting for the sndbuf space per association,
	 * so we only need to wake our own association.
	 */
	if (asoc->ep->sndbuf_policy)
		return __sctp_write_space(asoc);

	/* If association goes down and is just flushing its
	 * outq, then just normally notify others.
	 */
	if (asoc->base.dead)
		return sctp_write_space(sk);

	/* Accounting for the sndbuf space is per socket, so we
	 * need to wake up others, try to be fair and in case of
	 * other associations, let them have a go first instead
	 * of just doing a sctp_write_space() call.
	 *
	 * Note that we reach sctp_wake_up_waiters() only when
	 * associations free up queued chunks, thus we are under
	 * lock and the list of associations on a socket is
	 * guaranteed not to change.
	 */
	for (tmp = list_next_entry(tmp, asocs); 1;
	     tmp = list_next_entry(tmp, asocs)) {
		/* Manually skip the head element. */
		if (&tmp->asocs == &((sctp_sk(sk))->ep->asocs))
			continue;
		/* Wake up association. */
		__sctp_write_space(tmp);
		/* We've reached the end. */
		if (tmp == asoc)
			break;
	}
}