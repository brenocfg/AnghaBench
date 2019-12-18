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
struct nft_object {int dummy; } ;
struct nft_ct_expect_obj {int /*<<< orphan*/  size; int /*<<< orphan*/  timeout; int /*<<< orphan*/  dport; int /*<<< orphan*/  l4proto; int /*<<< orphan*/  l3num; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_CT_EXPECT_DPORT ; 
 int /*<<< orphan*/  NFTA_CT_EXPECT_L3PROTO ; 
 int /*<<< orphan*/  NFTA_CT_EXPECT_L4PROTO ; 
 int /*<<< orphan*/  NFTA_CT_EXPECT_SIZE ; 
 int /*<<< orphan*/  NFTA_CT_EXPECT_TIMEOUT ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct nft_ct_expect_obj* nft_obj_data (struct nft_object*) ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_ct_expect_obj_dump(struct sk_buff *skb,
				  struct nft_object *obj, bool reset)
{
	const struct nft_ct_expect_obj *priv = nft_obj_data(obj);

	if (nla_put_be16(skb, NFTA_CT_EXPECT_L3PROTO, htons(priv->l3num)) ||
	    nla_put_u8(skb, NFTA_CT_EXPECT_L4PROTO, priv->l4proto) ||
	    nla_put_be16(skb, NFTA_CT_EXPECT_DPORT, priv->dport) ||
	    nla_put_u32(skb, NFTA_CT_EXPECT_TIMEOUT, priv->timeout) ||
	    nla_put_u8(skb, NFTA_CT_EXPECT_SIZE, priv->size))
		return -1;

	return 0;
}