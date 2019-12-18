#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct TYPE_4__ {int type; int protocol; int /*<<< orphan*/  fwmark; int /*<<< orphan*/  timeout; int /*<<< orphan*/  dport; int /*<<< orphan*/  daddr; } ;
struct TYPE_3__ {int protocol; int /*<<< orphan*/  fwmark; int /*<<< orphan*/  timeout; int /*<<< orphan*/  dport; int /*<<< orphan*/  daddr; int /*<<< orphan*/  state; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
union ip_vs_sync_conn {TYPE_2__ v6; TYPE_1__ v4; } ;
struct netns_ipvs {int dummy; } ;
struct ip_vs_sync_v6 {int dummy; } ;
struct ip_vs_sync_v4 {int dummy; } ;
struct ip_vs_sync_conn_options {int dummy; } ;
struct ip_vs_protocol {unsigned int num_states; int /*<<< orphan*/  name; } ;
struct ip_vs_conn_param {int /*<<< orphan*/  pe; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u32 ;

/* Variables and functions */
 unsigned int AF_INET ; 
 unsigned int AF_INET6 ; 
 int IPVS_OPT_F_PARAM ; 
 int /*<<< orphan*/  IPVS_OPT_F_PE_DATA ; 
 int /*<<< orphan*/  IPVS_OPT_F_PE_NAME ; 
 int IPVS_OPT_F_SEQ_DATA ; 
#define  IPVS_OPT_PE_DATA 130 
#define  IPVS_OPT_PE_NAME 129 
#define  IPVS_OPT_SEQ_DATA 128 
 int IP_VS_CONN_F_BACKUP_MASK ; 
 int IP_VS_CONN_F_SYNC ; 
 int IP_VS_CONN_F_TEMPLATE ; 
 unsigned int IP_VS_CTPL_S_LAST ; 
 int /*<<< orphan*/  IP_VS_DBG (int,char*,...) ; 
 int /*<<< orphan*/  IP_VS_PEDATA_MAXLEN ; 
 int /*<<< orphan*/  IP_VS_PENAME_MAXLEN ; 
 int STYPE_F_INET6 ; 
 scalar_t__ ip_vs_conn_fill_param_sync (struct netns_ipvs*,unsigned int,union ip_vs_sync_conn*,struct ip_vs_conn_param*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ip_vs_pe_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_proc_conn (struct netns_ipvs*,struct ip_vs_conn_param*,int,unsigned int,int,unsigned int,union nf_inet_addr*,int /*<<< orphan*/ ,int,int,struct ip_vs_sync_conn_options*) ; 
 int /*<<< orphan*/  ip_vs_proc_seqopt (int /*<<< orphan*/ *,int,int*,struct ip_vs_sync_conn_options*) ; 
 int /*<<< orphan*/  ip_vs_proc_str (int /*<<< orphan*/ *,int,unsigned int*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct ip_vs_protocol* ip_vs_proto_get (int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 unsigned int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ip_vs_proc_sync_conn(struct netns_ipvs *ipvs, __u8 *p, __u8 *msg_end)
{
	struct ip_vs_sync_conn_options opt;
	union  ip_vs_sync_conn *s;
	struct ip_vs_protocol *pp;
	struct ip_vs_conn_param param;
	__u32 flags;
	unsigned int af, state, pe_data_len=0, pe_name_len=0;
	__u8 *pe_data=NULL, *pe_name=NULL;
	__u32 opt_flags=0;
	int retc=0;

	s = (union ip_vs_sync_conn *) p;

	if (s->v6.type & STYPE_F_INET6) {
#ifdef CONFIG_IP_VS_IPV6
		af = AF_INET6;
		p += sizeof(struct ip_vs_sync_v6);
#else
		IP_VS_DBG(3,"BACKUP, IPv6 msg received, and IPVS is not compiled for IPv6\n");
		retc = 10;
		goto out;
#endif
	} else if (!s->v4.type) {
		af = AF_INET;
		p += sizeof(struct ip_vs_sync_v4);
	} else {
		return -10;
	}
	if (p > msg_end)
		return -20;

	/* Process optional params check Type & Len. */
	while (p < msg_end) {
		int ptype;
		int plen;

		if (p+2 > msg_end)
			return -30;
		ptype = *(p++);
		plen  = *(p++);

		if (!plen || ((p + plen) > msg_end))
			return -40;
		/* Handle seq option  p = param data */
		switch (ptype & ~IPVS_OPT_F_PARAM) {
		case IPVS_OPT_SEQ_DATA:
			if (ip_vs_proc_seqopt(p, plen, &opt_flags, &opt))
				return -50;
			break;

		case IPVS_OPT_PE_DATA:
			if (ip_vs_proc_str(p, plen, &pe_data_len, &pe_data,
					   IP_VS_PEDATA_MAXLEN, &opt_flags,
					   IPVS_OPT_F_PE_DATA))
				return -60;
			break;

		case IPVS_OPT_PE_NAME:
			if (ip_vs_proc_str(p, plen,&pe_name_len, &pe_name,
					   IP_VS_PENAME_MAXLEN, &opt_flags,
					   IPVS_OPT_F_PE_NAME))
				return -70;
			break;

		default:
			/* Param data mandatory ? */
			if (!(ptype & IPVS_OPT_F_PARAM)) {
				IP_VS_DBG(3, "BACKUP, Unknown mandatory param %d found\n",
					  ptype & ~IPVS_OPT_F_PARAM);
				retc = 20;
				goto out;
			}
		}
		p += plen;  /* Next option */
	}

	/* Get flags and Mask off unsupported */
	flags  = ntohl(s->v4.flags) & IP_VS_CONN_F_BACKUP_MASK;
	flags |= IP_VS_CONN_F_SYNC;
	state = ntohs(s->v4.state);

	if (!(flags & IP_VS_CONN_F_TEMPLATE)) {
		pp = ip_vs_proto_get(s->v4.protocol);
		if (!pp) {
			IP_VS_DBG(3,"BACKUP, Unsupported protocol %u\n",
				s->v4.protocol);
			retc = 30;
			goto out;
		}
		if (state >= pp->num_states) {
			IP_VS_DBG(3, "BACKUP, Invalid %s state %u\n",
				pp->name, state);
			retc = 40;
			goto out;
		}
	} else {
		if (state >= IP_VS_CTPL_S_LAST)
			IP_VS_DBG(7, "BACKUP, Invalid tpl state %u\n",
				  state);
	}
	if (ip_vs_conn_fill_param_sync(ipvs, af, s, &param, pe_data,
				       pe_data_len, pe_name, pe_name_len)) {
		retc = 50;
		goto out;
	}
	/* If only IPv4, just silent skip IPv6 */
	if (af == AF_INET)
		ip_vs_proc_conn(ipvs, &param, flags, state, s->v4.protocol, af,
				(union nf_inet_addr *)&s->v4.daddr, s->v4.dport,
				ntohl(s->v4.timeout), ntohl(s->v4.fwmark),
				(opt_flags & IPVS_OPT_F_SEQ_DATA ? &opt : NULL)
				);
#ifdef CONFIG_IP_VS_IPV6
	else
		ip_vs_proc_conn(ipvs, &param, flags, state, s->v6.protocol, af,
				(union nf_inet_addr *)&s->v6.daddr, s->v6.dport,
				ntohl(s->v6.timeout), ntohl(s->v6.fwmark),
				(opt_flags & IPVS_OPT_F_SEQ_DATA ? &opt : NULL)
				);
#endif
	ip_vs_pe_put(param.pe);
	return 0;
	/* Error exit */
out:
	IP_VS_DBG(2, "BACKUP, Single msg dropped err:%d\n", retc);
	return retc;

}