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
struct sk_buff {int dummy; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int NF_ACCEPT ; 
 int /*<<< orphan*/  flush_expectations (struct nf_conn*,int) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 

__attribute__((used)) static int process_bye_request(struct sk_buff *skb, unsigned int protoff,
			       unsigned int dataoff,
			       const char **dptr, unsigned int *datalen,
			       unsigned int cseq)
{
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct = nf_ct_get(skb, &ctinfo);

	flush_expectations(ct, true);
	return NF_ACCEPT;
}