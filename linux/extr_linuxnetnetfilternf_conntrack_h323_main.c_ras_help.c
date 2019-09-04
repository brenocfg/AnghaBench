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
typedef  int /*<<< orphan*/  RasMessage ;

/* Variables and functions */
 size_t CTINFO2DIR (int) ; 
 int DecodeRasMessage (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int H323_ERROR_BOUND ; 
 int NF_ACCEPT ; 
 int NF_DROP ; 
 unsigned char* get_udp_data (struct sk_buff*,unsigned int,int*) ; 
 int /*<<< orphan*/  nf_ct_dump_tuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_helper_log (struct sk_buff*,struct nf_conn*,char*) ; 
 int /*<<< orphan*/  nf_h323_lock ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 scalar_t__ process_ras (struct sk_buff*,struct nf_conn*,int,unsigned int,unsigned char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ras_help(struct sk_buff *skb, unsigned int protoff,
		    struct nf_conn *ct, enum ip_conntrack_info ctinfo)
{
	static RasMessage ras;
	unsigned char *data;
	int datalen = 0;
	int ret;

	pr_debug("nf_ct_ras: skblen = %u\n", skb->len);

	spin_lock_bh(&nf_h323_lock);

	/* Get UDP data */
	data = get_udp_data(skb, protoff, &datalen);
	if (data == NULL)
		goto accept;
	pr_debug("nf_ct_ras: RAS message len=%d ", datalen);
	nf_ct_dump_tuple(&ct->tuplehash[CTINFO2DIR(ctinfo)].tuple);

	/* Decode RAS message */
	ret = DecodeRasMessage(data, datalen, &ras);
	if (ret < 0) {
		pr_debug("nf_ct_ras: decoding error: %s\n",
			 ret == H323_ERROR_BOUND ?
			 "out of bound" : "out of range");
		goto accept;
	}

	/* Process RAS message */
	if (process_ras(skb, ct, ctinfo, protoff, &data, &ras) < 0)
		goto drop;

      accept:
	spin_unlock_bh(&nf_h323_lock);
	return NF_ACCEPT;

      drop:
	spin_unlock_bh(&nf_h323_lock);
	nf_ct_helper_log(skb, ct, "cannot process RAS message");
	return NF_DROP;
}