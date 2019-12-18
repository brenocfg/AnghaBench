#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct sk_buff {int dummy; } ;
struct nf_ct_sip_master {scalar_t__ forced_dport; } ;
struct nf_conn {TYPE_8__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
typedef  scalar_t__ __be16 ;
struct TYPE_12__ {scalar_t__ port; } ;
struct TYPE_13__ {TYPE_4__ udp; } ;
struct TYPE_14__ {TYPE_5__ u; union nf_inet_addr u3; } ;
struct TYPE_9__ {scalar_t__ port; } ;
struct TYPE_10__ {TYPE_1__ udp; } ;
struct TYPE_11__ {TYPE_2__ u; union nf_inet_addr u3; } ;
struct TYPE_15__ {TYPE_6__ src; TYPE_3__ dst; } ;
struct TYPE_16__ {TYPE_7__ tuple; } ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
 int /*<<< orphan*/  INET6_ADDRSTRLEN ; 
 int mangle_packet (struct sk_buff*,unsigned int,unsigned int,char const**,unsigned int*,unsigned int,unsigned int,char*,unsigned int) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 scalar_t__ nf_inet_addr_cmp (union nf_inet_addr*,union nf_inet_addr*) ; 
 struct nf_ct_sip_master* nfct_help_data (struct nf_conn*) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 unsigned int sip_sprintf_addr_port (struct nf_conn*,char*,union nf_inet_addr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int map_addr(struct sk_buff *skb, unsigned int protoff,
		    unsigned int dataoff,
		    const char **dptr, unsigned int *datalen,
		    unsigned int matchoff, unsigned int matchlen,
		    union nf_inet_addr *addr, __be16 port)
{
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	enum ip_conntrack_dir dir = CTINFO2DIR(ctinfo);
	struct nf_ct_sip_master *ct_sip_info = nfct_help_data(ct);
	char buffer[INET6_ADDRSTRLEN + sizeof("[]:nnnnn")];
	unsigned int buflen;
	union nf_inet_addr newaddr;
	__be16 newport;

	if (nf_inet_addr_cmp(&ct->tuplehash[dir].tuple.src.u3, addr) &&
	    ct->tuplehash[dir].tuple.src.u.udp.port == port) {
		newaddr = ct->tuplehash[!dir].tuple.dst.u3;
		newport = ct->tuplehash[!dir].tuple.dst.u.udp.port;
	} else if (nf_inet_addr_cmp(&ct->tuplehash[dir].tuple.dst.u3, addr) &&
		   ct->tuplehash[dir].tuple.dst.u.udp.port == port) {
		newaddr = ct->tuplehash[!dir].tuple.src.u3;
		newport = ct_sip_info->forced_dport ? :
			  ct->tuplehash[!dir].tuple.src.u.udp.port;
	} else
		return 1;

	if (nf_inet_addr_cmp(&newaddr, addr) && newport == port)
		return 1;

	buflen = sip_sprintf_addr_port(ct, buffer, &newaddr, ntohs(newport));
	return mangle_packet(skb, protoff, dataoff, dptr, datalen,
			     matchoff, matchlen, buffer, buflen);
}