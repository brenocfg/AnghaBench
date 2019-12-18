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
struct TYPE_2__ {int /*<<< orphan*/  ip; } ;
struct ip_vs_dest_user_kern {int /*<<< orphan*/  tun_type; int /*<<< orphan*/  af; int /*<<< orphan*/  l_threshold; int /*<<< orphan*/  u_threshold; int /*<<< orphan*/  weight; int /*<<< orphan*/  conn_flags; int /*<<< orphan*/  port; TYPE_1__ addr; } ;
struct ip_vs_dest_user {int /*<<< orphan*/  l_threshold; int /*<<< orphan*/  u_threshold; int /*<<< orphan*/  weight; int /*<<< orphan*/  conn_flags; int /*<<< orphan*/  port; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  IP_VS_CONN_F_TUNNEL_TYPE_IPIP ; 
 int /*<<< orphan*/  memset (struct ip_vs_dest_user_kern*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ip_vs_copy_udest_compat(struct ip_vs_dest_user_kern *udest,
				   struct ip_vs_dest_user *udest_compat)
{
	memset(udest, 0, sizeof(*udest));

	udest->addr.ip		= udest_compat->addr;
	udest->port		= udest_compat->port;
	udest->conn_flags	= udest_compat->conn_flags;
	udest->weight		= udest_compat->weight;
	udest->u_threshold	= udest_compat->u_threshold;
	udest->l_threshold	= udest_compat->l_threshold;
	udest->af		= AF_INET;
	udest->tun_type		= IP_VS_CONN_F_TUNNEL_TYPE_IPIP;
}