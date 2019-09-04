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
struct ip_vs_timeout_user {int /*<<< orphan*/  udp_timeout; int /*<<< orphan*/  tcp_fin_timeout; int /*<<< orphan*/  tcp_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VS_DBG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_vs_set_timeout(struct netns_ipvs *ipvs, struct ip_vs_timeout_user *u)
{
#if defined(CONFIG_IP_VS_PROTO_TCP) || defined(CONFIG_IP_VS_PROTO_UDP)
	struct ip_vs_proto_data *pd;
#endif

	IP_VS_DBG(2, "Setting timeout tcp:%d tcpfin:%d udp:%d\n",
		  u->tcp_timeout,
		  u->tcp_fin_timeout,
		  u->udp_timeout);

#ifdef CONFIG_IP_VS_PROTO_TCP
	if (u->tcp_timeout < 0 || u->tcp_timeout > (INT_MAX / HZ) ||
	    u->tcp_fin_timeout < 0 || u->tcp_fin_timeout > (INT_MAX / HZ)) {
		return -EINVAL;
	}
#endif

#ifdef CONFIG_IP_VS_PROTO_UDP
	if (u->udp_timeout < 0 || u->udp_timeout > (INT_MAX / HZ))
		return -EINVAL;
#endif

#ifdef CONFIG_IP_VS_PROTO_TCP
	if (u->tcp_timeout) {
		pd = ip_vs_proto_data_get(ipvs, IPPROTO_TCP);
		pd->timeout_table[IP_VS_TCP_S_ESTABLISHED]
			= u->tcp_timeout * HZ;
	}

	if (u->tcp_fin_timeout) {
		pd = ip_vs_proto_data_get(ipvs, IPPROTO_TCP);
		pd->timeout_table[IP_VS_TCP_S_FIN_WAIT]
			= u->tcp_fin_timeout * HZ;
	}
#endif

#ifdef CONFIG_IP_VS_PROTO_UDP
	if (u->udp_timeout) {
		pd = ip_vs_proto_data_get(ipvs, IPPROTO_UDP);
		pd->timeout_table[IP_VS_UDP_S_NORMAL]
			= u->udp_timeout * HZ;
	}
#endif
	return 0;
}