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

/* Variables and functions */
 size_t NLMSG_ALIGN (int) ; 
 size_t nla_total_size (size_t) ; 

__attribute__((used)) static size_t igmpmsg_netlink_msgsize(size_t payloadlen)
{
	size_t len =
		NLMSG_ALIGN(sizeof(struct rtgenmsg))
		+ nla_total_size(1)	/* IPMRA_CREPORT_MSGTYPE */
		+ nla_total_size(4)	/* IPMRA_CREPORT_VIF_ID */
		+ nla_total_size(4)	/* IPMRA_CREPORT_SRC_ADDR */
		+ nla_total_size(4)	/* IPMRA_CREPORT_DST_ADDR */
					/* IPMRA_CREPORT_PKT */
		+ nla_total_size(payloadlen)
		;

	return len;
}