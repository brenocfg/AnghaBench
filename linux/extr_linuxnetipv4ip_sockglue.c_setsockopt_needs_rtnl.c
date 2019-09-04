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
#define  IP_ADD_MEMBERSHIP 141 
#define  IP_ADD_SOURCE_MEMBERSHIP 140 
#define  IP_BLOCK_SOURCE 139 
#define  IP_DROP_MEMBERSHIP 138 
#define  IP_DROP_SOURCE_MEMBERSHIP 137 
#define  IP_MSFILTER 136 
#define  IP_UNBLOCK_SOURCE 135 
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
	case IP_ADD_MEMBERSHIP:
	case IP_ADD_SOURCE_MEMBERSHIP:
	case IP_BLOCK_SOURCE:
	case IP_DROP_MEMBERSHIP:
	case IP_DROP_SOURCE_MEMBERSHIP:
	case IP_MSFILTER:
	case IP_UNBLOCK_SOURCE:
	case MCAST_BLOCK_SOURCE:
	case MCAST_MSFILTER:
	case MCAST_JOIN_GROUP:
	case MCAST_JOIN_SOURCE_GROUP:
	case MCAST_LEAVE_GROUP:
	case MCAST_LEAVE_SOURCE_GROUP:
	case MCAST_UNBLOCK_SOURCE:
		return true;
	}
	return false;
}