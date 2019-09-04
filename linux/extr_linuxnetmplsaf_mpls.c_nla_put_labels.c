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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct mpls_shim_hdr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 struct mpls_shim_hdr mpls_entry_encode (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mpls_shim_hdr* nla_data (struct nlattr*) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int,int) ; 

int nla_put_labels(struct sk_buff *skb, int attrtype,
		   u8 labels, const u32 label[])
{
	struct nlattr *nla;
	struct mpls_shim_hdr *nla_label;
	bool bos;
	int i;
	nla = nla_reserve(skb, attrtype, labels*4);
	if (!nla)
		return -EMSGSIZE;

	nla_label = nla_data(nla);
	bos = true;
	for (i = labels - 1; i >= 0; i--) {
		nla_label[i] = mpls_entry_encode(label[i], 0, 0, bos);
		bos = false;
	}

	return 0;
}