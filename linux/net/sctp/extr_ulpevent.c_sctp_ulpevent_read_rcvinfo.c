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
struct sctp_rcvinfo {int /*<<< orphan*/  rcv_context; int /*<<< orphan*/  rcv_assoc_id; int /*<<< orphan*/  rcv_cumtsn; int /*<<< orphan*/  rcv_tsn; int /*<<< orphan*/  rcv_flags; int /*<<< orphan*/  rcv_ppid; int /*<<< orphan*/  rcv_ssn; int /*<<< orphan*/  rcv_sid; } ;
struct msghdr {int dummy; } ;
typedef  int /*<<< orphan*/  rinfo ;
struct TYPE_2__ {int /*<<< orphan*/  default_rcv_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  SCTP_RCVINFO ; 
 int /*<<< orphan*/  memset (struct sctp_rcvinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct sctp_rcvinfo*) ; 
 int /*<<< orphan*/  sctp_assoc2id (TYPE_1__*) ; 
 scalar_t__ sctp_ulpevent_is_notification (struct sctp_ulpevent const*) ; 

void sctp_ulpevent_read_rcvinfo(const struct sctp_ulpevent *event,
				struct msghdr *msghdr)
{
	struct sctp_rcvinfo rinfo;

	if (sctp_ulpevent_is_notification(event))
		return;

	memset(&rinfo, 0, sizeof(struct sctp_rcvinfo));
	rinfo.rcv_sid = event->stream;
	rinfo.rcv_ssn = event->ssn;
	rinfo.rcv_ppid = event->ppid;
	rinfo.rcv_flags = event->flags;
	rinfo.rcv_tsn = event->tsn;
	rinfo.rcv_cumtsn = event->cumtsn;
	rinfo.rcv_assoc_id = sctp_assoc2id(event->asoc);
	rinfo.rcv_context = event->asoc->default_rcv_context;

	put_cmsg(msghdr, IPPROTO_SCTP, SCTP_RCVINFO,
		 sizeof(rinfo), &rinfo);
}