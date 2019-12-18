#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct nft_userdata {int /*<<< orphan*/  data; scalar_t__ len; } ;
struct nft_set_ext {int dummy; } ;
struct nft_set_elem {int /*<<< orphan*/  priv; } ;
struct nft_set {scalar_t__ dtype; int /*<<< orphan*/  dlen; int /*<<< orphan*/  klen; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ key; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  NFTA_LIST_ELEM ; 
 int /*<<< orphan*/  NFTA_SET_ELEM_DATA ; 
 int /*<<< orphan*/  NFTA_SET_ELEM_EXPIRATION ; 
 int /*<<< orphan*/  NFTA_SET_ELEM_EXPR ; 
 int /*<<< orphan*/  NFTA_SET_ELEM_FLAGS ; 
 int /*<<< orphan*/  NFTA_SET_ELEM_KEY ; 
 int /*<<< orphan*/  NFTA_SET_ELEM_OBJREF ; 
 int /*<<< orphan*/  NFTA_SET_ELEM_PAD ; 
 int /*<<< orphan*/  NFTA_SET_ELEM_TIMEOUT ; 
 int /*<<< orphan*/  NFTA_SET_ELEM_USERDATA ; 
 scalar_t__ NFT_DATA_VALUE ; 
 scalar_t__ NFT_DATA_VERDICT ; 
 int /*<<< orphan*/  NFT_SET_EXT_DATA ; 
 int /*<<< orphan*/  NFT_SET_EXT_EXPIRATION ; 
 int /*<<< orphan*/  NFT_SET_EXT_EXPR ; 
 int /*<<< orphan*/  NFT_SET_EXT_FLAGS ; 
 int /*<<< orphan*/  NFT_SET_EXT_OBJREF ; 
 int /*<<< orphan*/  NFT_SET_EXT_TIMEOUT ; 
 int /*<<< orphan*/  NFT_SET_EXT_USERDATA ; 
 scalar_t__ get_jiffies_64 () ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_jiffies64_to_msecs (scalar_t__) ; 
 scalar_t__ nft_data_dump (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ nft_expr_dump (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_set_ext* nft_set_elem_ext (struct nft_set const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_set_ext_data (struct nft_set_ext const*) ; 
 scalar_t__ nft_set_ext_exists (struct nft_set_ext const*,int /*<<< orphan*/ ) ; 
 scalar_t__* nft_set_ext_expiration (struct nft_set_ext const*) ; 
 int /*<<< orphan*/  nft_set_ext_expr (struct nft_set_ext const*) ; 
 int /*<<< orphan*/ * nft_set_ext_flags (struct nft_set_ext const*) ; 
 int /*<<< orphan*/  nft_set_ext_key (struct nft_set_ext const*) ; 
 TYPE_2__** nft_set_ext_obj (struct nft_set_ext const*) ; 
 scalar_t__* nft_set_ext_timeout (struct nft_set_ext const*) ; 
 struct nft_userdata* nft_set_ext_userdata (struct nft_set_ext const*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be64 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 scalar_t__ time_before64 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int nf_tables_fill_setelem(struct sk_buff *skb,
				  const struct nft_set *set,
				  const struct nft_set_elem *elem)
{
	const struct nft_set_ext *ext = nft_set_elem_ext(set, elem->priv);
	unsigned char *b = skb_tail_pointer(skb);
	struct nlattr *nest;

	nest = nla_nest_start_noflag(skb, NFTA_LIST_ELEM);
	if (nest == NULL)
		goto nla_put_failure;

	if (nft_data_dump(skb, NFTA_SET_ELEM_KEY, nft_set_ext_key(ext),
			  NFT_DATA_VALUE, set->klen) < 0)
		goto nla_put_failure;

	if (nft_set_ext_exists(ext, NFT_SET_EXT_DATA) &&
	    nft_data_dump(skb, NFTA_SET_ELEM_DATA, nft_set_ext_data(ext),
			  set->dtype == NFT_DATA_VERDICT ? NFT_DATA_VERDICT : NFT_DATA_VALUE,
			  set->dlen) < 0)
		goto nla_put_failure;

	if (nft_set_ext_exists(ext, NFT_SET_EXT_EXPR) &&
	    nft_expr_dump(skb, NFTA_SET_ELEM_EXPR, nft_set_ext_expr(ext)) < 0)
		goto nla_put_failure;

	if (nft_set_ext_exists(ext, NFT_SET_EXT_OBJREF) &&
	    nla_put_string(skb, NFTA_SET_ELEM_OBJREF,
			   (*nft_set_ext_obj(ext))->key.name) < 0)
		goto nla_put_failure;

	if (nft_set_ext_exists(ext, NFT_SET_EXT_FLAGS) &&
	    nla_put_be32(skb, NFTA_SET_ELEM_FLAGS,
		         htonl(*nft_set_ext_flags(ext))))
		goto nla_put_failure;

	if (nft_set_ext_exists(ext, NFT_SET_EXT_TIMEOUT) &&
	    nla_put_be64(skb, NFTA_SET_ELEM_TIMEOUT,
			 nf_jiffies64_to_msecs(*nft_set_ext_timeout(ext)),
			 NFTA_SET_ELEM_PAD))
		goto nla_put_failure;

	if (nft_set_ext_exists(ext, NFT_SET_EXT_EXPIRATION)) {
		u64 expires, now = get_jiffies_64();

		expires = *nft_set_ext_expiration(ext);
		if (time_before64(now, expires))
			expires -= now;
		else
			expires = 0;

		if (nla_put_be64(skb, NFTA_SET_ELEM_EXPIRATION,
				 nf_jiffies64_to_msecs(expires),
				 NFTA_SET_ELEM_PAD))
			goto nla_put_failure;
	}

	if (nft_set_ext_exists(ext, NFT_SET_EXT_USERDATA)) {
		struct nft_userdata *udata;

		udata = nft_set_ext_userdata(ext);
		if (nla_put(skb, NFTA_SET_ELEM_USERDATA,
			    udata->len + 1, udata->data))
			goto nla_put_failure;
	}

	nla_nest_end(skb, nest);
	return 0;

nla_put_failure:
	nlmsg_trim(skb, b);
	return -EMSGSIZE;
}