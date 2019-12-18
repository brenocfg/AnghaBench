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
typedef  scalar_t__ u16 ;
struct udphdr {int /*<<< orphan*/  check; int /*<<< orphan*/  len; } ;
struct snmp_ctx {scalar_t__ from; scalar_t__ to; unsigned char* begin; int /*<<< orphan*/ * check; } ;
struct sk_buff {int dummy; } ;
struct nf_conn {TYPE_6__* tuplehash; } ;
struct iphdr {int ihl; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_9__ {scalar_t__ ip; } ;
struct TYPE_10__ {TYPE_3__ u3; } ;
struct TYPE_7__ {scalar_t__ ip; } ;
struct TYPE_8__ {TYPE_1__ u3; } ;
struct TYPE_11__ {TYPE_4__ dst; TYPE_2__ src; } ;
struct TYPE_12__ {TYPE_5__ tuple; } ;

/* Variables and functions */
 int IP_CT_DIR_ORIGINAL ; 
 int NF_ACCEPT ; 
 int NF_DROP ; 
 int asn1_ber_decoder (int /*<<< orphan*/ *,struct snmp_ctx*,char*,scalar_t__) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_ct_helper_log (struct sk_buff*,struct nf_conn*,char*) ; 
 int /*<<< orphan*/  nf_nat_snmp_basic_decoder ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snmp_translate(struct nf_conn *ct, int dir, struct sk_buff *skb)
{
	struct iphdr *iph = ip_hdr(skb);
	struct udphdr *udph = (struct udphdr *)((__be32 *)iph + iph->ihl);
	u16 datalen = ntohs(udph->len) - sizeof(struct udphdr);
	char *data = (unsigned char *)udph + sizeof(struct udphdr);
	struct snmp_ctx ctx;
	int ret;

	if (dir == IP_CT_DIR_ORIGINAL) {
		ctx.from = ct->tuplehash[dir].tuple.src.u3.ip;
		ctx.to = ct->tuplehash[!dir].tuple.dst.u3.ip;
	} else {
		ctx.from = ct->tuplehash[!dir].tuple.src.u3.ip;
		ctx.to = ct->tuplehash[dir].tuple.dst.u3.ip;
	}

	if (ctx.from == ctx.to)
		return NF_ACCEPT;

	ctx.begin = (unsigned char *)udph + sizeof(struct udphdr);
	ctx.check = &udph->check;
	ret = asn1_ber_decoder(&nf_nat_snmp_basic_decoder, &ctx, data, datalen);
	if (ret < 0) {
		nf_ct_helper_log(skb, ct, "parser failed\n");
		return NF_DROP;
	}

	return NF_ACCEPT;
}