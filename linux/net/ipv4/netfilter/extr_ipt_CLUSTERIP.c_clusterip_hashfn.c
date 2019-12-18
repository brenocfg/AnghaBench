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
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct iphdr {int ihl; int /*<<< orphan*/  saddr; int /*<<< orphan*/  protocol; } ;
struct clusterip_config {int hash_mode; int /*<<< orphan*/  num_total_nodes; int /*<<< orphan*/  hash_initval; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CLUSTERIP_HASHMODE_SIP 130 
#define  CLUSTERIP_HASHMODE_SIP_SPT 129 
#define  CLUSTERIP_HASHMODE_SIP_SPT_DPT 128 
 struct iphdr* ip_hdr (struct sk_buff const*) ; 
 unsigned long jhash_1word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long jhash_2words (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long jhash_3words (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_info_ratelimited (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int proto_ports_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ reciprocal_scale (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_header_pointer (struct sk_buff const*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u_int32_t
clusterip_hashfn(const struct sk_buff *skb,
		 const struct clusterip_config *config)
{
	const struct iphdr *iph = ip_hdr(skb);
	unsigned long hashval;
	u_int16_t sport = 0, dport = 0;
	int poff;

	poff = proto_ports_offset(iph->protocol);
	if (poff >= 0) {
		const u_int16_t *ports;
		u16 _ports[2];

		ports = skb_header_pointer(skb, iph->ihl * 4 + poff, 4, _ports);
		if (ports) {
			sport = ports[0];
			dport = ports[1];
		}
	} else {
		net_info_ratelimited("unknown protocol %u\n", iph->protocol);
	}

	switch (config->hash_mode) {
	case CLUSTERIP_HASHMODE_SIP:
		hashval = jhash_1word(ntohl(iph->saddr),
				      config->hash_initval);
		break;
	case CLUSTERIP_HASHMODE_SIP_SPT:
		hashval = jhash_2words(ntohl(iph->saddr), sport,
				       config->hash_initval);
		break;
	case CLUSTERIP_HASHMODE_SIP_SPT_DPT:
		hashval = jhash_3words(ntohl(iph->saddr), sport, dport,
				       config->hash_initval);
		break;
	default:
		/* to make gcc happy */
		hashval = 0;
		/* This cannot happen, unless the check function wasn't called
		 * at rule load time */
		pr_info("unknown mode %u\n", config->hash_mode);
		BUG();
		break;
	}

	/* node numbers are 1..n, not 0..n */
	return reciprocal_scale(hashval, config->num_total_nodes) + 1;
}