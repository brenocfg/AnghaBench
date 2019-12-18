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

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 scalar_t__ inet_add_protocol (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_inetaddr_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_inetaddr_notifier ; 
 int /*<<< orphan*/  sctp_protocol ; 

__attribute__((used)) static int sctp_v4_add_protocol(void)
{
	/* Register notifier for inet address additions/deletions. */
	register_inetaddr_notifier(&sctp_inetaddr_notifier);

	/* Register SCTP with inet layer.  */
	if (inet_add_protocol(&sctp_protocol, IPPROTO_SCTP) < 0)
		return -EAGAIN;

	return 0;
}