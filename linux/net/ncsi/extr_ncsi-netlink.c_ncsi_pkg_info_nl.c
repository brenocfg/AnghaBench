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
struct ncsi_dev_priv {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NCSI_ATTR_IFINDEX ; 
 size_t NCSI_ATTR_PACKAGE_ID ; 
 int /*<<< orphan*/  NCSI_ATTR_PACKAGE_LIST ; 
 int /*<<< orphan*/  NCSI_CMD_PKG_INFO ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 struct sk_buff* genlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ncsi_genl_family ; 
 int ncsi_write_package_info (struct sk_buff*,struct ncsi_dev_priv*,unsigned int) ; 
 struct ncsi_dev_priv* ndp_from_ifindex (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int nla_get_u32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ncsi_pkg_info_nl(struct sk_buff *msg, struct genl_info *info)
{
	struct ncsi_dev_priv *ndp;
	unsigned int package_id;
	struct sk_buff *skb;
	struct nlattr *attr;
	void *hdr;
	int rc;

	if (!info || !info->attrs)
		return -EINVAL;

	if (!info->attrs[NCSI_ATTR_IFINDEX])
		return -EINVAL;

	if (!info->attrs[NCSI_ATTR_PACKAGE_ID])
		return -EINVAL;

	ndp = ndp_from_ifindex(genl_info_net(info),
			       nla_get_u32(info->attrs[NCSI_ATTR_IFINDEX]));
	if (!ndp)
		return -ENODEV;

	skb = genlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;

	hdr = genlmsg_put(skb, info->snd_portid, info->snd_seq,
			  &ncsi_genl_family, 0, NCSI_CMD_PKG_INFO);
	if (!hdr) {
		kfree_skb(skb);
		return -EMSGSIZE;
	}

	package_id = nla_get_u32(info->attrs[NCSI_ATTR_PACKAGE_ID]);

	attr = nla_nest_start_noflag(skb, NCSI_ATTR_PACKAGE_LIST);
	if (!attr) {
		kfree_skb(skb);
		return -EMSGSIZE;
	}
	rc = ncsi_write_package_info(skb, ndp, package_id);

	if (rc) {
		nla_nest_cancel(skb, attr);
		goto err;
	}

	nla_nest_end(skb, attr);

	genlmsg_end(skb, hdr);
	return genlmsg_reply(skb, info);

err:
	kfree_skb(skb);
	return rc;
}