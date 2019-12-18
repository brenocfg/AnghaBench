#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
typedef  scalar_t__ u_int16_t ;
struct sk_buff {int dummy; } ;
struct nf_ct_sip_master {scalar_t__ forced_dport; } ;
struct TYPE_18__ {scalar_t__ port; } ;
struct TYPE_19__ {TYPE_13__ udp; } ;
struct TYPE_28__ {scalar_t__ port; } ;
struct TYPE_15__ {TYPE_9__ udp; } ;
struct TYPE_16__ {TYPE_10__ u; union nf_inet_addr u3; } ;
struct TYPE_17__ {TYPE_11__ dst; } ;
struct nf_conntrack_expect {int dir; TYPE_14__ saved_proto; TYPE_12__ tuple; union nf_inet_addr saved_addr; int /*<<< orphan*/  expectfn; } ;
struct nf_conn {TYPE_8__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
typedef  scalar_t__ __be16 ;
struct TYPE_23__ {scalar_t__ port; } ;
struct TYPE_24__ {TYPE_4__ udp; } ;
struct TYPE_25__ {TYPE_5__ u; union nf_inet_addr u3; } ;
struct TYPE_20__ {scalar_t__ port; } ;
struct TYPE_21__ {TYPE_1__ udp; } ;
struct TYPE_22__ {TYPE_2__ u; union nf_inet_addr u3; } ;
struct TYPE_26__ {TYPE_6__ dst; TYPE_3__ src; } ;
struct TYPE_27__ {TYPE_7__ tuple; } ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  INET6_ADDRSTRLEN ; 
 unsigned int NF_ACCEPT ; 
 int /*<<< orphan*/  NF_CT_EXP_F_SKIP_MASTER ; 
 unsigned int NF_DROP ; 
 scalar_t__ htons (scalar_t__) ; 
 int /*<<< orphan*/  mangle_packet (struct sk_buff*,unsigned int,unsigned int,char const**,unsigned int*,unsigned int,unsigned int,char*,unsigned int) ; 
 int nf_ct_expect_related (struct nf_conntrack_expect*,int /*<<< orphan*/ ) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_ct_helper_log (struct sk_buff*,struct nf_conn*,char*) ; 
 int /*<<< orphan*/  nf_ct_unexpect_related (struct nf_conntrack_expect*) ; 
 scalar_t__ nf_inet_addr_cmp (union nf_inet_addr*,union nf_inet_addr*) ; 
 int /*<<< orphan*/  nf_nat_sip_expected ; 
 struct nf_ct_sip_master* nfct_help_data (struct nf_conn*) ; 
 scalar_t__ ntohs (scalar_t__) ; 
 unsigned int sip_sprintf_addr_port (struct nf_conn*,char*,union nf_inet_addr*,scalar_t__) ; 

__attribute__((used)) static unsigned int nf_nat_sip_expect(struct sk_buff *skb, unsigned int protoff,
				      unsigned int dataoff,
				      const char **dptr, unsigned int *datalen,
				      struct nf_conntrack_expect *exp,
				      unsigned int matchoff,
				      unsigned int matchlen)
{
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	enum ip_conntrack_dir dir = CTINFO2DIR(ctinfo);
	struct nf_ct_sip_master *ct_sip_info = nfct_help_data(ct);
	union nf_inet_addr newaddr;
	u_int16_t port;
	__be16 srcport;
	char buffer[INET6_ADDRSTRLEN + sizeof("[]:nnnnn")];
	unsigned int buflen;

	/* Connection will come from reply */
	if (nf_inet_addr_cmp(&ct->tuplehash[dir].tuple.src.u3,
			     &ct->tuplehash[!dir].tuple.dst.u3))
		newaddr = exp->tuple.dst.u3;
	else
		newaddr = ct->tuplehash[!dir].tuple.dst.u3;

	/* If the signalling port matches the connection's source port in the
	 * original direction, try to use the destination port in the opposite
	 * direction. */
	srcport = ct_sip_info->forced_dport ? :
		  ct->tuplehash[dir].tuple.src.u.udp.port;
	if (exp->tuple.dst.u.udp.port == srcport)
		port = ntohs(ct->tuplehash[!dir].tuple.dst.u.udp.port);
	else
		port = ntohs(exp->tuple.dst.u.udp.port);

	exp->saved_addr = exp->tuple.dst.u3;
	exp->tuple.dst.u3 = newaddr;
	exp->saved_proto.udp.port = exp->tuple.dst.u.udp.port;
	exp->dir = !dir;
	exp->expectfn = nf_nat_sip_expected;

	for (; port != 0; port++) {
		int ret;

		exp->tuple.dst.u.udp.port = htons(port);
		ret = nf_ct_expect_related(exp, NF_CT_EXP_F_SKIP_MASTER);
		if (ret == 0)
			break;
		else if (ret != -EBUSY) {
			port = 0;
			break;
		}
	}

	if (port == 0) {
		nf_ct_helper_log(skb, ct, "all ports in use for SIP");
		return NF_DROP;
	}

	if (!nf_inet_addr_cmp(&exp->tuple.dst.u3, &exp->saved_addr) ||
	    exp->tuple.dst.u.udp.port != exp->saved_proto.udp.port) {
		buflen = sip_sprintf_addr_port(ct, buffer, &newaddr, port);
		if (!mangle_packet(skb, protoff, dataoff, dptr, datalen,
				   matchoff, matchlen, buffer, buflen)) {
			nf_ct_helper_log(skb, ct, "cannot mangle packet");
			goto err;
		}
	}
	return NF_ACCEPT;

err:
	nf_ct_unexpect_related(exp);
	return NF_DROP;
}