#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_dm_hw_metadata {int /*<<< orphan*/  trap_name; int /*<<< orphan*/  trap_group_name; } ;
struct TYPE_2__ {scalar_t__ hdrsize; } ;

/* Variables and functions */
 scalar_t__ GENL_HDRLEN ; 
 size_t NLMSG_ALIGN (size_t) ; 
 size_t net_dm_in_port_size () ; 
 TYPE_1__ net_drop_monitor_family ; 
 size_t nla_total_size (size_t) ; 
 size_t nlmsg_msg_size (scalar_t__) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
net_dm_hw_packet_report_size(size_t payload_len,
			     const struct net_dm_hw_metadata *hw_metadata)
{
	size_t size;

	size = nlmsg_msg_size(GENL_HDRLEN + net_drop_monitor_family.hdrsize);

	return NLMSG_ALIGN(size) +
	       /* NET_DM_ATTR_ORIGIN */
	       nla_total_size(sizeof(u16)) +
	       /* NET_DM_ATTR_HW_TRAP_GROUP_NAME */
	       nla_total_size(strlen(hw_metadata->trap_group_name) + 1) +
	       /* NET_DM_ATTR_HW_TRAP_NAME */
	       nla_total_size(strlen(hw_metadata->trap_name) + 1) +
	       /* NET_DM_ATTR_IN_PORT */
	       net_dm_in_port_size() +
	       /* NET_DM_ATTR_TIMESTAMP */
	       nla_total_size(sizeof(u64)) +
	       /* NET_DM_ATTR_ORIG_LEN */
	       nla_total_size(sizeof(u32)) +
	       /* NET_DM_ATTR_PROTO */
	       nla_total_size(sizeof(u16)) +
	       /* NET_DM_ATTR_PAYLOAD */
	       nla_total_size(payload_len);
}