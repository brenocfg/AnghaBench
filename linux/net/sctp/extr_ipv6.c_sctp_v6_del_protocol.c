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
 int /*<<< orphan*/  inet6_del_protocol (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_inet6addr_notifier ; 
 int /*<<< orphan*/  sctpv6_protocol ; 
 int /*<<< orphan*/  unregister_inet6addr_notifier (int /*<<< orphan*/ *) ; 

void sctp_v6_del_protocol(void)
{
	inet6_del_protocol(&sctpv6_protocol, IPPROTO_SCTP);
	unregister_inet6addr_notifier(&sctp_inet6addr_notifier);
}