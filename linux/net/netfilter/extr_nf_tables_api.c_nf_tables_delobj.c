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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nft_table {scalar_t__ use; } ;
struct nft_object {scalar_t__ use; } ;
struct nft_ctx {int dummy; } ;
struct nfgenmsg {int nfgen_family; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct nft_table*) ; 
 size_t NFTA_OBJ_HANDLE ; 
 size_t NFTA_OBJ_NAME ; 
 size_t NFTA_OBJ_TABLE ; 
 size_t NFTA_OBJ_TYPE ; 
 int /*<<< orphan*/  NL_SET_BAD_ATTR (struct netlink_ext_ack*,struct nlattr const*) ; 
 int PTR_ERR (struct nft_table*) ; 
 int /*<<< orphan*/  nft_ctx_init (struct nft_ctx*,struct net*,struct sk_buff*,struct nlmsghdr const*,int,struct nft_table*,int /*<<< orphan*/ *,struct nlattr const* const*) ; 
 int nft_delobj (struct nft_ctx*,struct nft_table*) ; 
 int /*<<< orphan*/  nft_genmask_next (struct net*) ; 
 struct nft_table* nft_obj_lookup (struct net*,struct nft_table*,struct nlattr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_table* nft_obj_lookup_byhandle (struct nft_table*,struct nlattr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_table* nft_table_lookup (struct net*,struct nlattr const* const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr const*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nf_tables_delobj(struct net *net, struct sock *nlsk,
			    struct sk_buff *skb, const struct nlmsghdr *nlh,
			    const struct nlattr * const nla[],
			    struct netlink_ext_ack *extack)
{
	const struct nfgenmsg *nfmsg = nlmsg_data(nlh);
	u8 genmask = nft_genmask_next(net);
	int family = nfmsg->nfgen_family;
	const struct nlattr *attr;
	struct nft_table *table;
	struct nft_object *obj;
	struct nft_ctx ctx;
	u32 objtype;

	if (!nla[NFTA_OBJ_TYPE] ||
	    (!nla[NFTA_OBJ_NAME] && !nla[NFTA_OBJ_HANDLE]))
		return -EINVAL;

	table = nft_table_lookup(net, nla[NFTA_OBJ_TABLE], family, genmask);
	if (IS_ERR(table)) {
		NL_SET_BAD_ATTR(extack, nla[NFTA_OBJ_TABLE]);
		return PTR_ERR(table);
	}

	objtype = ntohl(nla_get_be32(nla[NFTA_OBJ_TYPE]));
	if (nla[NFTA_OBJ_HANDLE]) {
		attr = nla[NFTA_OBJ_HANDLE];
		obj = nft_obj_lookup_byhandle(table, attr, objtype, genmask);
	} else {
		attr = nla[NFTA_OBJ_NAME];
		obj = nft_obj_lookup(net, table, attr, objtype, genmask);
	}

	if (IS_ERR(obj)) {
		NL_SET_BAD_ATTR(extack, attr);
		return PTR_ERR(obj);
	}
	if (obj->use > 0) {
		NL_SET_BAD_ATTR(extack, attr);
		return -EBUSY;
	}

	nft_ctx_init(&ctx, net, skb, nlh, family, table, NULL, nla);

	return nft_delobj(&ctx, obj);
}