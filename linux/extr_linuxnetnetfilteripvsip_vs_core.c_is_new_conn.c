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
struct tcphdr {int syn; int /*<<< orphan*/  type; } ;
struct sk_buff {int dummy; } ;
struct sctphdr {int dummy; } ;
struct sctp_chunkhdr {int syn; int /*<<< orphan*/  type; } ;
struct ip_vs_iphdr {int protocol; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  schunk ;
typedef  int /*<<< orphan*/  _tcph ;

/* Variables and functions */
#define  IPPROTO_SCTP 129 
#define  IPPROTO_TCP 128 
 int /*<<< orphan*/  SCTP_CID_INIT ; 
 struct tcphdr* skb_header_pointer (struct sk_buff const*,int /*<<< orphan*/ ,int,struct tcphdr*) ; 

__attribute__((used)) static inline bool is_new_conn(const struct sk_buff *skb,
			       struct ip_vs_iphdr *iph)
{
	switch (iph->protocol) {
	case IPPROTO_TCP: {
		struct tcphdr _tcph, *th;

		th = skb_header_pointer(skb, iph->len, sizeof(_tcph), &_tcph);
		if (th == NULL)
			return false;
		return th->syn;
	}
	case IPPROTO_SCTP: {
		struct sctp_chunkhdr *sch, schunk;

		sch = skb_header_pointer(skb, iph->len + sizeof(struct sctphdr),
					 sizeof(schunk), &schunk);
		if (sch == NULL)
			return false;
		return sch->type == SCTP_CID_INIT;
	}
	default:
		return false;
	}
}