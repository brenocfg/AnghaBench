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
struct netns_ipvs {int /*<<< orphan*/ * rs_table; } ;
struct ip_vs_dest {int in_rs_table; int /*<<< orphan*/  d_list; int /*<<< orphan*/  addr; int /*<<< orphan*/  af; int /*<<< orphan*/  tun_port; int /*<<< orphan*/  tun_type; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  IP_VS_CONN_F_MASQ 132 
#define  IP_VS_CONN_F_TUNNEL 131 
#define  IP_VS_CONN_F_TUNNEL_TYPE_GRE 130 
#define  IP_VS_CONN_F_TUNNEL_TYPE_GUE 129 
#define  IP_VS_CONN_F_TUNNEL_TYPE_IPIP 128 
 int IP_VS_DFWD_METHOD (struct ip_vs_dest*) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int ip_vs_rs_hashkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ip_vs_rs_hash(struct netns_ipvs *ipvs, struct ip_vs_dest *dest)
{
	unsigned int hash;
	__be16 port;

	if (dest->in_rs_table)
		return;

	switch (IP_VS_DFWD_METHOD(dest)) {
	case IP_VS_CONN_F_MASQ:
		port = dest->port;
		break;
	case IP_VS_CONN_F_TUNNEL:
		switch (dest->tun_type) {
		case IP_VS_CONN_F_TUNNEL_TYPE_GUE:
			port = dest->tun_port;
			break;
		case IP_VS_CONN_F_TUNNEL_TYPE_IPIP:
		case IP_VS_CONN_F_TUNNEL_TYPE_GRE:
			port = 0;
			break;
		default:
			return;
		}
		break;
	default:
		return;
	}

	/*
	 *	Hash by proto,addr,port,
	 *	which are the parameters of the real service.
	 */
	hash = ip_vs_rs_hashkey(dest->af, &dest->addr, port);

	hlist_add_head_rcu(&dest->d_list, &ipvs->rs_table[hash]);
	dest->in_rs_table = 1;
}