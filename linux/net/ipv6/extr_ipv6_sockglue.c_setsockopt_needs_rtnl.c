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
#define  IPV6_ADDRFORM 139 
#define  IPV6_ADD_MEMBERSHIP 138 
#define  IPV6_DROP_MEMBERSHIP 137 
#define  IPV6_JOIN_ANYCAST 136 
#define  IPV6_LEAVE_ANYCAST 135 
#define  MCAST_BLOCK_SOURCE 134 
#define  MCAST_JOIN_GROUP 133 
#define  MCAST_JOIN_SOURCE_GROUP 132 
#define  MCAST_LEAVE_GROUP 131 
#define  MCAST_LEAVE_SOURCE_GROUP 130 
#define  MCAST_MSFILTER 129 
#define  MCAST_UNBLOCK_SOURCE 128 

__attribute__((used)) static bool setsockopt_needs_rtnl(int optname)
{
	switch (optname) {
	case IPV6_ADDRFORM:
	case IPV6_ADD_MEMBERSHIP:
	case IPV6_DROP_MEMBERSHIP:
	case IPV6_JOIN_ANYCAST:
	case IPV6_LEAVE_ANYCAST:
	case MCAST_JOIN_GROUP:
	case MCAST_LEAVE_GROUP:
	case MCAST_JOIN_SOURCE_GROUP:
	case MCAST_LEAVE_SOURCE_GROUP:
	case MCAST_BLOCK_SOURCE:
	case MCAST_UNBLOCK_SOURCE:
	case MCAST_MSFILTER:
		return true;
	}
	return false;
}