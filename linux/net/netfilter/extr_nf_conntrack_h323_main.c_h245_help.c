#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {char* len; } ;
struct nf_conn {TYPE_1__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_2__ {int /*<<< orphan*/  tuple; } ;
typedef  int /*<<< orphan*/  MultimediaSystemControlMessage ;

/* Variables and functions */
 size_t CTINFO2DIR (int) ; 
 int DecodeMultimediaSystemControlMessage (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int H323_ERROR_BOUND ; 
 int IP_CT_ESTABLISHED ; 
 int IP_CT_ESTABLISHED_REPLY ; 
 int NF_ACCEPT ; 
 int NF_DROP ; 
 scalar_t__ get_tpkt_data (struct sk_buff*,unsigned int,struct nf_conn*,int,unsigned char**,int*,int*) ; 
 int /*<<< orphan*/  nf_ct_dump_tuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_helper_log (struct sk_buff*,struct nf_conn*,char*) ; 
 int /*<<< orphan*/  nf_h323_lock ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 scalar_t__ process_h245 (struct sk_buff*,struct nf_conn*,int,unsigned int,unsigned char**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int h245_help(struct sk_buff *skb, unsigned int protoff,
		     struct nf_conn *ct, enum ip_conntrack_info ctinfo)
{
	static MultimediaSystemControlMessage mscm;
	unsigned char *data = NULL;
	int datalen;
	int dataoff;
	int ret;

	/* Until there's been traffic both ways, don't look in packets. */
	if (ctinfo != IP_CT_ESTABLISHED && ctinfo != IP_CT_ESTABLISHED_REPLY)
		return NF_ACCEPT;

	pr_debug("nf_ct_h245: skblen = %u\n", skb->len);

	spin_lock_bh(&nf_h323_lock);

	/* Process each TPKT */
	while (get_tpkt_data(skb, protoff, ct, ctinfo,
			     &data, &datalen, &dataoff)) {
		pr_debug("nf_ct_h245: TPKT len=%d ", datalen);
		nf_ct_dump_tuple(&ct->tuplehash[CTINFO2DIR(ctinfo)].tuple);

		/* Decode H.245 signal */
		ret = DecodeMultimediaSystemControlMessage(data, datalen,
							   &mscm);
		if (ret < 0) {
			pr_debug("nf_ct_h245: decoding error: %s\n",
				 ret == H323_ERROR_BOUND ?
				 "out of bound" : "out of range");
			/* We don't drop when decoding error */
			break;
		}

		/* Process H.245 signal */
		if (process_h245(skb, ct, ctinfo, protoff,
				 &data, dataoff, &mscm) < 0)
			goto drop;
	}

	spin_unlock_bh(&nf_h323_lock);
	return NF_ACCEPT;

      drop:
	spin_unlock_bh(&nf_h323_lock);
	nf_ct_helper_log(skb, ct, "cannot process H.245 message");
	return NF_DROP;
}