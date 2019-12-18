#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union sctp_subtype {scalar_t__ chunk; } ;
struct sctp_ulpevent {int dummy; } ;
struct sctp_cmd_seq {int dummy; } ;
struct sctp_chunk {int dummy; } ;
struct TYPE_6__ {unsigned int error; } ;
struct TYPE_5__ {TYPE_1__* si; } ;
struct sctp_association {scalar_t__ overall_error_count; scalar_t__ max_retrans; TYPE_3__ outqueue; int /*<<< orphan*/  ulpq; TYPE_2__ stream; } ;
typedef  enum sctp_event_type { ____Placeholder_sctp_event_type } sctp_event_type ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_4__ {int /*<<< orphan*/  (* abort_pd ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCTP_CHUNK (struct sctp_chunk*) ; 
 scalar_t__ SCTP_CID_ABORT ; 
 int /*<<< orphan*/  SCTP_CMD_DELETE_TCB ; 
 int /*<<< orphan*/  SCTP_CMD_EVENT_ULP ; 
 int /*<<< orphan*/  SCTP_CMD_NEW_STATE ; 
 int /*<<< orphan*/  SCTP_CMD_REPLY ; 
 int /*<<< orphan*/  SCTP_COMM_LOST ; 
 int SCTP_EVENT_T_CHUNK ; 
 int /*<<< orphan*/  SCTP_NULL () ; 
 int /*<<< orphan*/  SCTP_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_STATE_CLOSED ; 
 int /*<<< orphan*/  SCTP_ULPEVENT (struct sctp_ulpevent*) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (struct sctp_cmd_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_chunk* sctp_make_violation_max_retrans (struct sctp_association*,struct sctp_chunk*) ; 
 struct sctp_ulpevent* sctp_ulpevent_make_assoc_change (struct sctp_association*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sctp_cmd_assoc_failed(struct sctp_cmd_seq *commands,
				  struct sctp_association *asoc,
				  enum sctp_event_type event_type,
				  union sctp_subtype subtype,
				  struct sctp_chunk *chunk,
				  unsigned int error)
{
	struct sctp_ulpevent *event;
	struct sctp_chunk *abort;

	/* Cancel any partial delivery in progress. */
	asoc->stream.si->abort_pd(&asoc->ulpq, GFP_ATOMIC);

	if (event_type == SCTP_EVENT_T_CHUNK && subtype.chunk == SCTP_CID_ABORT)
		event = sctp_ulpevent_make_assoc_change(asoc, 0, SCTP_COMM_LOST,
						(__u16)error, 0, 0, chunk,
						GFP_ATOMIC);
	else
		event = sctp_ulpevent_make_assoc_change(asoc, 0, SCTP_COMM_LOST,
						(__u16)error, 0, 0, NULL,
						GFP_ATOMIC);
	if (event)
		sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP,
				SCTP_ULPEVENT(event));

	if (asoc->overall_error_count >= asoc->max_retrans) {
		abort = sctp_make_violation_max_retrans(asoc, chunk);
		if (abort)
			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(abort));
	}

	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_CLOSED));

	/* SEND_FAILED sent later when cleaning up the association. */
	asoc->outqueue.error = error;
	sctp_add_cmd_sf(commands, SCTP_CMD_DELETE_TCB, SCTP_NULL());
}