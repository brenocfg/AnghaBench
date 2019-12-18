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
struct sk_buff {int dummy; } ;
struct nfc_target {scalar_t__ nfcid1_len; scalar_t__ sensb_res_len; scalar_t__ sensf_res_len; int /*<<< orphan*/  iso15693_uid; int /*<<< orphan*/  iso15693_dsfid; scalar_t__ is_iso15693; int /*<<< orphan*/  sensf_res; int /*<<< orphan*/  sensb_res; int /*<<< orphan*/  nfcid1; int /*<<< orphan*/  sel_res; int /*<<< orphan*/  sens_res; int /*<<< orphan*/  supported_protocols; int /*<<< orphan*/  idx; } ;
struct netlink_callback {TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFC_ATTR_PROTOCOLS ; 
 int /*<<< orphan*/  NFC_ATTR_TARGET_INDEX ; 
 int /*<<< orphan*/  NFC_ATTR_TARGET_ISO15693_DSFID ; 
 int /*<<< orphan*/  NFC_ATTR_TARGET_ISO15693_UID ; 
 int /*<<< orphan*/  NFC_ATTR_TARGET_NFCID1 ; 
 int /*<<< orphan*/  NFC_ATTR_TARGET_SEL_RES ; 
 int /*<<< orphan*/  NFC_ATTR_TARGET_SENSB_RES ; 
 int /*<<< orphan*/  NFC_ATTR_TARGET_SENSF_RES ; 
 int /*<<< orphan*/  NFC_ATTR_TARGET_SENS_RES ; 
 int /*<<< orphan*/  NFC_CMD_GET_TARGET ; 
 int /*<<< orphan*/  genl_dump_check_consistent (struct netlink_callback*,void*) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_genl_family ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfc_genl_send_target(struct sk_buff *msg, struct nfc_target *target,
				struct netlink_callback *cb, int flags)
{
	void *hdr;

	hdr = genlmsg_put(msg, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &nfc_genl_family, flags, NFC_CMD_GET_TARGET);
	if (!hdr)
		return -EMSGSIZE;

	genl_dump_check_consistent(cb, hdr);

	if (nla_put_u32(msg, NFC_ATTR_TARGET_INDEX, target->idx) ||
	    nla_put_u32(msg, NFC_ATTR_PROTOCOLS, target->supported_protocols) ||
	    nla_put_u16(msg, NFC_ATTR_TARGET_SENS_RES, target->sens_res) ||
	    nla_put_u8(msg, NFC_ATTR_TARGET_SEL_RES, target->sel_res))
		goto nla_put_failure;
	if (target->nfcid1_len > 0 &&
	    nla_put(msg, NFC_ATTR_TARGET_NFCID1, target->nfcid1_len,
		    target->nfcid1))
		goto nla_put_failure;
	if (target->sensb_res_len > 0 &&
	    nla_put(msg, NFC_ATTR_TARGET_SENSB_RES, target->sensb_res_len,
		    target->sensb_res))
		goto nla_put_failure;
	if (target->sensf_res_len > 0 &&
	    nla_put(msg, NFC_ATTR_TARGET_SENSF_RES, target->sensf_res_len,
		    target->sensf_res))
		goto nla_put_failure;

	if (target->is_iso15693) {
		if (nla_put_u8(msg, NFC_ATTR_TARGET_ISO15693_DSFID,
			       target->iso15693_dsfid) ||
		    nla_put(msg, NFC_ATTR_TARGET_ISO15693_UID,
			    sizeof(target->iso15693_uid), target->iso15693_uid))
			goto nla_put_failure;
	}

	genlmsg_end(msg, hdr);
	return 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}