#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int16_t ;
struct sk_buff {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  port; } ;
struct TYPE_10__ {TYPE_3__ tcp; } ;
struct TYPE_11__ {TYPE_4__ u; } ;
struct TYPE_12__ {TYPE_5__ dst; } ;
struct TYPE_7__ {int /*<<< orphan*/  port; } ;
struct TYPE_8__ {TYPE_1__ tcp; } ;
struct nf_conntrack_expect {int /*<<< orphan*/  master; TYPE_6__ tuple; TYPE_2__ saved_proto; int /*<<< orphan*/  expectfn; int /*<<< orphan*/  dir; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IP_CT_DIR_ORIGINAL ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int nf_ct_expect_related (struct nf_conntrack_expect*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_helper_log (struct sk_buff*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nf_ct_unexpect_related (struct nf_conntrack_expect*) ; 
 int /*<<< orphan*/  nf_nat_follow_master ; 
 int /*<<< orphan*/  nf_nat_mangle_udp_packet (struct sk_buff*,int /*<<< orphan*/ ,int,unsigned int,unsigned int,unsigned int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static unsigned int help(struct sk_buff *skb,
			 enum ip_conntrack_info ctinfo,
			 unsigned int protoff,
			 unsigned int matchoff,
			 unsigned int matchlen,
			 struct nf_conntrack_expect *exp)
{
	char buffer[sizeof("65535")];
	u_int16_t port;

	/* Connection comes from client. */
	exp->saved_proto.tcp.port = exp->tuple.dst.u.tcp.port;
	exp->dir = IP_CT_DIR_ORIGINAL;

	/* When you see the packet, we need to NAT it the same as the
	 * this one (ie. same IP: it will be TCP and master is UDP). */
	exp->expectfn = nf_nat_follow_master;

	/* Try to get same port: if not, try to change it. */
	for (port = ntohs(exp->saved_proto.tcp.port); port != 0; port++) {
		int res;

		exp->tuple.dst.u.tcp.port = htons(port);
		res = nf_ct_expect_related(exp, 0);
		if (res == 0)
			break;
		else if (res != -EBUSY) {
			port = 0;
			break;
		}
	}

	if (port == 0) {
		nf_ct_helper_log(skb, exp->master, "all ports in use");
		return NF_DROP;
	}

	sprintf(buffer, "%u", port);
	if (!nf_nat_mangle_udp_packet(skb, exp->master, ctinfo,
				      protoff, matchoff, matchlen,
				      buffer, strlen(buffer))) {
		nf_ct_helper_log(skb, exp->master, "cannot mangle packet");
		nf_ct_unexpect_related(exp);
		return NF_DROP;
	}
	return NF_ACCEPT;
}