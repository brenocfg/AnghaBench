#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct TYPE_5__ {int /*<<< orphan*/  vport; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  cport; int /*<<< orphan*/  caddr; int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {int /*<<< orphan*/  vport; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  cport; int /*<<< orphan*/  caddr; int /*<<< orphan*/  protocol; } ;
union ip_vs_sync_conn {TYPE_2__ v4; TYPE_1__ v6; } ;
struct netns_ipvs {int dummy; } ;
struct ip_vs_conn_param {unsigned int pe_data_len; TYPE_3__* pe; int /*<<< orphan*/  pe_data; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_6__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int AF_INET6 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IP_VS_DBG (int,char*,char*) ; 
 int /*<<< orphan*/  IP_VS_ERR_RL (char*) ; 
 int /*<<< orphan*/  IP_VS_PENAME_MAXLEN ; 
 TYPE_3__* __ip_vs_pe_getbyname (char*) ; 
 int /*<<< orphan*/  ip_vs_conn_fill_param (struct netns_ipvs*,int,int /*<<< orphan*/ ,union nf_inet_addr const*,int /*<<< orphan*/ ,union nf_inet_addr const*,int /*<<< orphan*/ ,struct ip_vs_conn_param*) ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
ip_vs_conn_fill_param_sync(struct netns_ipvs *ipvs, int af, union ip_vs_sync_conn *sc,
			   struct ip_vs_conn_param *p,
			   __u8 *pe_data, unsigned int pe_data_len,
			   __u8 *pe_name, unsigned int pe_name_len)
{
#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		ip_vs_conn_fill_param(ipvs, af, sc->v6.protocol,
				      (const union nf_inet_addr *)&sc->v6.caddr,
				      sc->v6.cport,
				      (const union nf_inet_addr *)&sc->v6.vaddr,
				      sc->v6.vport, p);
	else
#endif
		ip_vs_conn_fill_param(ipvs, af, sc->v4.protocol,
				      (const union nf_inet_addr *)&sc->v4.caddr,
				      sc->v4.cport,
				      (const union nf_inet_addr *)&sc->v4.vaddr,
				      sc->v4.vport, p);
	/* Handle pe data */
	if (pe_data_len) {
		if (pe_name_len) {
			char buff[IP_VS_PENAME_MAXLEN+1];

			memcpy(buff, pe_name, pe_name_len);
			buff[pe_name_len]=0;
			p->pe = __ip_vs_pe_getbyname(buff);
			if (!p->pe) {
				IP_VS_DBG(3, "BACKUP, no %s engine found/loaded\n",
					     buff);
				return 1;
			}
		} else {
			IP_VS_ERR_RL("BACKUP, Invalid PE parameters\n");
			return 1;
		}

		p->pe_data = kmemdup(pe_data, pe_data_len, GFP_ATOMIC);
		if (!p->pe_data) {
			module_put(p->pe->module);
			return -ENOMEM;
		}
		p->pe_data_len = pe_data_len;
	}
	return 0;
}