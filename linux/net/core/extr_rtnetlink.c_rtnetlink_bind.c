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
struct net {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EPERM ; 
#define  RTNLGRP_IPV4_MROUTE_R 129 
#define  RTNLGRP_IPV6_MROUTE_R 128 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtnetlink_bind(struct net *net, int group)
{
	switch (group) {
	case RTNLGRP_IPV4_MROUTE_R:
	case RTNLGRP_IPV6_MROUTE_R:
		if (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			return -EPERM;
		break;
	}
	return 0;
}