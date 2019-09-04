#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_4__ {int count; int /*<<< orphan*/ * item; } ;
struct TYPE_5__ {int options; TYPE_1__ fastStart; int /*<<< orphan*/  h245Address; } ;
typedef  TYPE_2__ Connect_UUIE ;

/* Variables and functions */
 int eConnect_UUIE_fastStart ; 
 int eConnect_UUIE_h245Address ; 
 int expect_h245 (struct sk_buff*,struct nf_conn*,int,unsigned int,unsigned char**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int process_olc (struct sk_buff*,struct nf_conn*,int,unsigned int,unsigned char**,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int process_connect(struct sk_buff *skb, struct nf_conn *ct,
			   enum ip_conntrack_info ctinfo,
			   unsigned int protoff,
			   unsigned char **data, int dataoff,
			   Connect_UUIE *connect)
{
	int ret;
	int i;

	pr_debug("nf_ct_q931: Connect\n");

	if (connect->options & eConnect_UUIE_h245Address) {
		ret = expect_h245(skb, ct, ctinfo, protoff, data, dataoff,
				  &connect->h245Address);
		if (ret < 0)
			return -1;
	}

	if (connect->options & eConnect_UUIE_fastStart) {
		for (i = 0; i < connect->fastStart.count; i++) {
			ret = process_olc(skb, ct, ctinfo,
					  protoff, data, dataoff,
					  &connect->fastStart.item[i]);
			if (ret < 0)
				return -1;
		}
	}

	return 0;
}