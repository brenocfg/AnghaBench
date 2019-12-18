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
struct net_bridge_mdb_entry {int dummy; } ;
struct net_bridge {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip4; } ;
struct br_ip {int /*<<< orphan*/  vid; int /*<<< orphan*/  proto; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  br_dst ;
typedef  int /*<<< orphan*/  __u16 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 struct net_bridge_mdb_entry* br_mdb_ip_get (struct net_bridge*,struct br_ip*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct br_ip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct net_bridge_mdb_entry *br_mdb_ip4_get(struct net_bridge *br,
						   __be32 dst, __u16 vid)
{
	struct br_ip br_dst;

	memset(&br_dst, 0, sizeof(br_dst));
	br_dst.u.ip4 = dst;
	br_dst.proto = htons(ETH_P_IP);
	br_dst.vid = vid;

	return br_mdb_ip_get(br, &br_dst);
}