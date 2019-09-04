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
struct smc_pnetentry {int dummy; } ;
struct sk_buff {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  SMC_PNETID_GET ; 
 size_t SMC_PNETID_NAME ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 scalar_t__ nla_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct smc_pnetentry* smc_pnet_find_pnetid (char*) ; 
 int /*<<< orphan*/  smc_pnet_nl_family ; 
 scalar_t__ smc_pnet_set_nla (struct sk_buff*,struct smc_pnetentry*) ; 

__attribute__((used)) static int smc_pnet_get(struct sk_buff *skb, struct genl_info *info)
{
	struct smc_pnetentry *pnetelem;
	struct sk_buff *msg;
	void *hdr;
	int rc;

	if (!info->attrs[SMC_PNETID_NAME])
		return -EINVAL;
	pnetelem = smc_pnet_find_pnetid(
				(char *)nla_data(info->attrs[SMC_PNETID_NAME]));
	if (!pnetelem)
		return -ENOENT;
	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	hdr = genlmsg_put(msg, info->snd_portid, info->snd_seq,
			  &smc_pnet_nl_family, 0, SMC_PNETID_GET);
	if (!hdr) {
		rc = -EMSGSIZE;
		goto err_out;
	}

	if (smc_pnet_set_nla(msg, pnetelem)) {
		rc = -ENOBUFS;
		goto err_out;
	}

	genlmsg_end(msg, hdr);
	return genlmsg_reply(msg, info);

err_out:
	nlmsg_free(msg);
	return rc;
}