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
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  inet_del_protocol (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_inetaddr_notifier ; 
 int /*<<< orphan*/  sctp_protocol ; 
 int /*<<< orphan*/  unregister_inetaddr_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sctp_v4_del_protocol(void)
{
	inet_del_protocol(&sctp_protocol, IPPROTO_SCTP);
	unregister_inetaddr_notifier(&sctp_inetaddr_notifier);
}