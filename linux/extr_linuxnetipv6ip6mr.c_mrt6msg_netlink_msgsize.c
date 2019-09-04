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
struct rtgenmsg {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 size_t NLMSG_ALIGN (int) ; 
 size_t nla_total_size (size_t) ; 

__attribute__((used)) static size_t mrt6msg_netlink_msgsize(size_t payloadlen)
{
	size_t len =
		NLMSG_ALIGN(sizeof(struct rtgenmsg))
		+ nla_total_size(1)	/* IP6MRA_CREPORT_MSGTYPE */
		+ nla_total_size(4)	/* IP6MRA_CREPORT_MIF_ID */
					/* IP6MRA_CREPORT_SRC_ADDR */
		+ nla_total_size(sizeof(struct in6_addr))
					/* IP6MRA_CREPORT_DST_ADDR */
		+ nla_total_size(sizeof(struct in6_addr))
					/* IP6MRA_CREPORT_PKT */
		+ nla_total_size(payloadlen)
		;

	return len;
}