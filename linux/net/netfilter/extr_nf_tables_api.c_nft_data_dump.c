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
struct nlattr {int dummy; } ;
struct nft_data {int /*<<< orphan*/  verdict; } ;
typedef  enum nft_data_types { ____Placeholder_nft_data_types } nft_data_types ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NFTA_DATA_VERDICT ; 
#define  NFT_DATA_VALUE 129 
#define  NFT_DATA_VERDICT 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int nft_value_dump (struct sk_buff*,struct nft_data const*,unsigned int) ; 
 int nft_verdict_dump (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int) ; 

int nft_data_dump(struct sk_buff *skb, int attr, const struct nft_data *data,
		  enum nft_data_types type, unsigned int len)
{
	struct nlattr *nest;
	int err;

	nest = nla_nest_start_noflag(skb, attr);
	if (nest == NULL)
		return -1;

	switch (type) {
	case NFT_DATA_VALUE:
		err = nft_value_dump(skb, data, len);
		break;
	case NFT_DATA_VERDICT:
		err = nft_verdict_dump(skb, NFTA_DATA_VERDICT, &data->verdict);
		break;
	default:
		err = -EINVAL;
		WARN_ON(1);
	}

	nla_nest_end(skb, nest);
	return err;
}