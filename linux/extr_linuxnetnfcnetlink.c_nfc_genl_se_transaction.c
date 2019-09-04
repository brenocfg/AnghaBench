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
struct sk_buff {int dummy; } ;
struct nfc_se {int /*<<< orphan*/  type; } ;
struct nfc_evt_transaction {int /*<<< orphan*/  params; int /*<<< orphan*/  params_len; int /*<<< orphan*/  aid; int /*<<< orphan*/  aid_len; } ;
struct nfc_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFC_ATTR_DEVICE_INDEX ; 
 int /*<<< orphan*/  NFC_ATTR_SE_AID ; 
 int /*<<< orphan*/  NFC_ATTR_SE_INDEX ; 
 int /*<<< orphan*/  NFC_ATTR_SE_PARAMS ; 
 int /*<<< orphan*/  NFC_ATTR_SE_TYPE ; 
 int /*<<< orphan*/  NFC_EVENT_SE_TRANSACTION ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct nfc_evt_transaction*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_multicast (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfc_se* nfc_find_se (struct nfc_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_genl_family ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nfc_genl_se_transaction(struct nfc_dev *dev, u8 se_idx,
			    struct nfc_evt_transaction *evt_transaction)
{
	struct nfc_se *se;
	struct sk_buff *msg;
	void *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	hdr = genlmsg_put(msg, 0, 0, &nfc_genl_family, 0,
			  NFC_EVENT_SE_TRANSACTION);
	if (!hdr)
		goto free_msg;

	se = nfc_find_se(dev, se_idx);
	if (!se)
		goto free_msg;

	if (nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, dev->idx) ||
	    nla_put_u32(msg, NFC_ATTR_SE_INDEX, se_idx) ||
	    nla_put_u8(msg, NFC_ATTR_SE_TYPE, se->type) ||
	    nla_put(msg, NFC_ATTR_SE_AID, evt_transaction->aid_len,
		    evt_transaction->aid) ||
	    nla_put(msg, NFC_ATTR_SE_PARAMS, evt_transaction->params_len,
		    evt_transaction->params))
		goto nla_put_failure;

	/* evt_transaction is no more used */
	devm_kfree(&dev->dev, evt_transaction);

	genlmsg_end(msg, hdr);

	genlmsg_multicast(&nfc_genl_family, msg, 0, 0, GFP_KERNEL);

	return 0;

nla_put_failure:
free_msg:
	/* evt_transaction is no more used */
	devm_kfree(&dev->dev, evt_transaction);
	nlmsg_free(msg);
	return -EMSGSIZE;
}