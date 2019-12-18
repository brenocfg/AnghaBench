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
struct bridge_mcast_own_query {int dummy; } ;
struct net_bridge_port {struct bridge_mcast_own_query ip4_own_query; } ;
struct net_bridge {int /*<<< orphan*/  ip4_other_query; struct bridge_mcast_own_query ip4_own_query; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip4; } ;
struct br_ip {int /*<<< orphan*/  vid; int /*<<< orphan*/  proto; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  br_group ;
typedef  int /*<<< orphan*/  __u16 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  br_multicast_leave_group (struct net_bridge*,struct net_bridge_port*,struct br_ip*,int /*<<< orphan*/ *,struct bridge_mcast_own_query*,unsigned char const*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_local_multicast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct br_ip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void br_ip4_multicast_leave_group(struct net_bridge *br,
					 struct net_bridge_port *port,
					 __be32 group,
					 __u16 vid,
					 const unsigned char *src)
{
	struct br_ip br_group;
	struct bridge_mcast_own_query *own_query;

	if (ipv4_is_local_multicast(group))
		return;

	own_query = port ? &port->ip4_own_query : &br->ip4_own_query;

	memset(&br_group, 0, sizeof(br_group));
	br_group.u.ip4 = group;
	br_group.proto = htons(ETH_P_IP);
	br_group.vid = vid;

	br_multicast_leave_group(br, port, &br_group, &br->ip4_other_query,
				 own_query, src);
}