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
struct netns_ipvs {int dummy; } ;
struct ip_vs_timeout_user {void* udp_timeout; void* tcp_fin_timeout; void* tcp_timeout; } ;
struct ip_vs_proto_data {void** timeout_table; } ;

/* Variables and functions */
 void* HZ ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 size_t IP_VS_TCP_S_ESTABLISHED ; 
 size_t IP_VS_TCP_S_FIN_WAIT ; 
 size_t IP_VS_UDP_S_NORMAL ; 
 struct ip_vs_proto_data* ip_vs_proto_data_get (struct netns_ipvs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ip_vs_timeout_user*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
__ip_vs_get_timeouts(struct netns_ipvs *ipvs, struct ip_vs_timeout_user *u)
{
#if defined(CONFIG_IP_VS_PROTO_TCP) || defined(CONFIG_IP_VS_PROTO_UDP)
	struct ip_vs_proto_data *pd;
#endif

	memset(u, 0, sizeof (*u));

#ifdef CONFIG_IP_VS_PROTO_TCP
	pd = ip_vs_proto_data_get(ipvs, IPPROTO_TCP);
	u->tcp_timeout = pd->timeout_table[IP_VS_TCP_S_ESTABLISHED] / HZ;
	u->tcp_fin_timeout = pd->timeout_table[IP_VS_TCP_S_FIN_WAIT] / HZ;
#endif
#ifdef CONFIG_IP_VS_PROTO_UDP
	pd = ip_vs_proto_data_get(ipvs, IPPROTO_UDP);
	u->udp_timeout =
			pd->timeout_table[IP_VS_UDP_S_NORMAL] / HZ;
#endif
}