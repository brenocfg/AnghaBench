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
typedef  int /*<<< orphan*/  u32 ;
struct ovs_header {int dummy; } ;
struct ovs_dp_stats {int dummy; } ;
struct ovs_dp_megaflow_stats {int dummy; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 size_t NLMSG_ALIGN (int) ; 
 scalar_t__ nla_total_size (int) ; 
 scalar_t__ nla_total_size_64bit (int) ; 

__attribute__((used)) static size_t ovs_dp_cmd_msg_size(void)
{
	size_t msgsize = NLMSG_ALIGN(sizeof(struct ovs_header));

	msgsize += nla_total_size(IFNAMSIZ);
	msgsize += nla_total_size_64bit(sizeof(struct ovs_dp_stats));
	msgsize += nla_total_size_64bit(sizeof(struct ovs_dp_megaflow_stats));
	msgsize += nla_total_size(sizeof(u32)); /* OVS_DP_ATTR_USER_FEATURES */

	return msgsize;
}