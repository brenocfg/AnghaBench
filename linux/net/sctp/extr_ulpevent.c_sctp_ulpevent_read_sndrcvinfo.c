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
struct sctp_ulpevent {TYPE_1__* asoc; int /*<<< orphan*/  cumtsn; int /*<<< orphan*/  tsn; int /*<<< orphan*/  flags; int /*<<< orphan*/  ppid; int /*<<< orphan*/  ssn; int /*<<< orphan*/  stream; } ;
struct sctp_sndrcvinfo {scalar_t__ sinfo_timetolive; int /*<<< orphan*/  sinfo_context; int /*<<< orphan*/  sinfo_assoc_id; int /*<<< orphan*/  sinfo_cumtsn; int /*<<< orphan*/  sinfo_tsn; int /*<<< orphan*/  sinfo_flags; int /*<<< orphan*/  sinfo_ppid; int /*<<< orphan*/  sinfo_ssn; int /*<<< orphan*/  sinfo_stream; } ;
struct msghdr {int dummy; } ;
typedef  int /*<<< orphan*/  sinfo ;
struct TYPE_2__ {int /*<<< orphan*/  default_rcv_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  SCTP_SNDRCV ; 
 int /*<<< orphan*/  memset (struct sctp_sndrcvinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct sctp_sndrcvinfo*) ; 
 int /*<<< orphan*/  sctp_assoc2id (TYPE_1__*) ; 
 scalar_t__ sctp_ulpevent_is_notification (struct sctp_ulpevent const*) ; 

void sctp_ulpevent_read_sndrcvinfo(const struct sctp_ulpevent *event,
				   struct msghdr *msghdr)
{
	struct sctp_sndrcvinfo sinfo;

	if (sctp_ulpevent_is_notification(event))
		return;

	memset(&sinfo, 0, sizeof(sinfo));
	sinfo.sinfo_stream = event->stream;
	sinfo.sinfo_ssn = event->ssn;
	sinfo.sinfo_ppid = event->ppid;
	sinfo.sinfo_flags = event->flags;
	sinfo.sinfo_tsn = event->tsn;
	sinfo.sinfo_cumtsn = event->cumtsn;
	sinfo.sinfo_assoc_id = sctp_assoc2id(event->asoc);
	/* Context value that is set via SCTP_CONTEXT socket option. */
	sinfo.sinfo_context = event->asoc->default_rcv_context;
	/* These fields are not used while receiving. */
	sinfo.sinfo_timetolive = 0;

	put_cmsg(msghdr, IPPROTO_SCTP, SCTP_SNDRCV,
		 sizeof(sinfo), &sinfo);
}