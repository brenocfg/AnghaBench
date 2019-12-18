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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct sctp_ulpevent {int /*<<< orphan*/  asoc; int /*<<< orphan*/  flags; int /*<<< orphan*/  ppid; int /*<<< orphan*/  stream; } ;
struct sctp_nxtinfo {int /*<<< orphan*/  nxt_assoc_id; int /*<<< orphan*/  nxt_length; int /*<<< orphan*/  nxt_flags; int /*<<< orphan*/  nxt_ppid; int /*<<< orphan*/  nxt_sid; } ;
struct msghdr {int dummy; } ;
typedef  int /*<<< orphan*/  nxtinfo ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  SCTP_NOTIFICATION ; 
 int /*<<< orphan*/  SCTP_NXTINFO ; 
 int /*<<< orphan*/  memset (struct sctp_nxtinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct sctp_nxtinfo*) ; 
 int /*<<< orphan*/  sctp_assoc2id (int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_ulpevent_is_notification (struct sctp_ulpevent const*) ; 

__attribute__((used)) static void __sctp_ulpevent_read_nxtinfo(const struct sctp_ulpevent *event,
					 struct msghdr *msghdr,
					 const struct sk_buff *skb)
{
	struct sctp_nxtinfo nxtinfo;

	memset(&nxtinfo, 0, sizeof(nxtinfo));
	nxtinfo.nxt_sid = event->stream;
	nxtinfo.nxt_ppid = event->ppid;
	nxtinfo.nxt_flags = event->flags;
	if (sctp_ulpevent_is_notification(event))
		nxtinfo.nxt_flags |= SCTP_NOTIFICATION;
	nxtinfo.nxt_length = skb->len;
	nxtinfo.nxt_assoc_id = sctp_assoc2id(event->asoc);

	put_cmsg(msghdr, IPPROTO_SCTP, SCTP_NXTINFO,
		 sizeof(nxtinfo), &nxtinfo);
}