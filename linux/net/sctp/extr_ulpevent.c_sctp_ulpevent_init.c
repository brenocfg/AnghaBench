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
struct sctp_ulpevent {unsigned int rmem_len; int /*<<< orphan*/  msg_flags; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct sctp_ulpevent*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sctp_ulpevent_init(struct sctp_ulpevent *event,
			       __u16 msg_flags,
			       unsigned int len)
{
	memset(event, 0, sizeof(struct sctp_ulpevent));
	event->msg_flags = msg_flags;
	event->rmem_len = len;
}