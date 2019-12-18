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
struct sctp_transport {int /*<<< orphan*/  rto; } ;
struct sctp_cmd_seq {int dummy; } ;
struct sctp_chunk {struct sctp_transport* transport; } ;
struct sctp_association {int /*<<< orphan*/ * timeouts; struct sctp_transport* shutdown_last_sent_to; } ;

/* Variables and functions */
 size_t SCTP_EVENT_TIMEOUT_T2_SHUTDOWN ; 
 struct sctp_transport* sctp_assoc_choose_alter_transport (struct sctp_association*,struct sctp_transport*) ; 

__attribute__((used)) static void sctp_cmd_setup_t2(struct sctp_cmd_seq *cmds,
			      struct sctp_association *asoc,
			      struct sctp_chunk *chunk)
{
	struct sctp_transport *t;

	if (chunk->transport)
		t = chunk->transport;
	else {
		t = sctp_assoc_choose_alter_transport(asoc,
					      asoc->shutdown_last_sent_to);
		chunk->transport = t;
	}
	asoc->shutdown_last_sent_to = t;
	asoc->timeouts[SCTP_EVENT_TIMEOUT_T2_SHUTDOWN] = t->rto;
}