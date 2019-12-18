#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
union nf_inet_addr {int /*<<< orphan*/  ip; } ;
typedef  scalar_t__ u_int16_t ;
struct sk_buff {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  port; } ;
struct TYPE_16__ {TYPE_6__ tcp; } ;
struct TYPE_17__ {TYPE_7__ u; } ;
struct TYPE_18__ {TYPE_8__ dst; } ;
struct TYPE_13__ {int /*<<< orphan*/  port; } ;
struct TYPE_14__ {TYPE_4__ tcp; } ;
struct nf_conntrack_expect {size_t dir; TYPE_9__ tuple; TYPE_5__ saved_proto; int /*<<< orphan*/  expectfn; struct nf_conn* master; } ;
struct nf_conn {TYPE_3__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_10__ {union nf_inet_addr u3; } ;
struct TYPE_11__ {TYPE_1__ dst; } ;
struct TYPE_12__ {TYPE_2__ tuple; } ;

/* Variables and functions */
 int EBUSY ; 
 size_t IP_CT_DIR_REPLY ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int nf_ct_expect_related (struct nf_conntrack_expect*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_helper_log (struct sk_buff*,struct nf_conn*,char*) ; 
 int /*<<< orphan*/  nf_ct_unexpect_related (struct nf_conntrack_expect*) ; 
 int /*<<< orphan*/  nf_nat_follow_master ; 
 int /*<<< orphan*/  nf_nat_mangle_tcp_packet (struct sk_buff*,struct nf_conn*,int,unsigned int,unsigned int,unsigned int,char*,int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static unsigned int help(struct sk_buff *skb,
			 enum ip_conntrack_info ctinfo,
			 unsigned int protoff,
			 unsigned int matchoff,
			 unsigned int matchlen,
			 struct nf_conntrack_expect *exp)
{
	char buffer[sizeof("4294967296 65635")];
	struct nf_conn *ct = exp->master;
	union nf_inet_addr newaddr;
	u_int16_t port;

	/* Reply comes from server. */
	newaddr = ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3;

	exp->saved_proto.tcp.port = exp->tuple.dst.u.tcp.port;
	exp->dir = IP_CT_DIR_REPLY;
	exp->expectfn = nf_nat_follow_master;

	/* Try to get same port: if not, try to change it. */
	for (port = ntohs(exp->saved_proto.tcp.port); port != 0; port++) {
		int ret;

		exp->tuple.dst.u.tcp.port = htons(port);
		ret = nf_ct_expect_related(exp, 0);
		if (ret == 0)
			break;
		else if (ret != -EBUSY) {
			port = 0;
			break;
		}
	}

	if (port == 0) {
		nf_ct_helper_log(skb, ct, "all ports in use");
		return NF_DROP;
	}

	/* strlen("\1DCC CHAT chat AAAAAAAA P\1\n")=27
	 * strlen("\1DCC SCHAT chat AAAAAAAA P\1\n")=28
	 * strlen("\1DCC SEND F AAAAAAAA P S\1\n")=26
	 * strlen("\1DCC MOVE F AAAAAAAA P S\1\n")=26
	 * strlen("\1DCC TSEND F AAAAAAAA P S\1\n")=27
	 *
	 * AAAAAAAAA: bound addr (1.0.0.0==16777216, min 8 digits,
	 *                        255.255.255.255==4294967296, 10 digits)
	 * P:         bound port (min 1 d, max 5d (65635))
	 * F:         filename   (min 1 d )
	 * S:         size       (min 1 d )
	 * 0x01, \n:  terminators
	 */
	/* AAA = "us", ie. where server normally talks to. */
	snprintf(buffer, sizeof(buffer), "%u %u", ntohl(newaddr.ip), port);
	pr_debug("inserting '%s' == %pI4, port %u\n",
		 buffer, &newaddr.ip, port);

	if (!nf_nat_mangle_tcp_packet(skb, ct, ctinfo, protoff, matchoff,
				      matchlen, buffer, strlen(buffer))) {
		nf_ct_helper_log(skb, ct, "cannot mangle packet");
		nf_ct_unexpect_related(exp);
		return NF_DROP;
	}

	return NF_ACCEPT;
}