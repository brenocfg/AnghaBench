#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nfc_llcp_local {int /*<<< orphan*/  miux; int /*<<< orphan*/  rw; int /*<<< orphan*/  lto; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  NFC_ATTR_DEVICE_INDEX ; 
 int /*<<< orphan*/  NFC_ATTR_LLC_PARAM_LTO ; 
 int /*<<< orphan*/  NFC_ATTR_LLC_PARAM_MIUX ; 
 int /*<<< orphan*/  NFC_ATTR_LLC_PARAM_RW ; 
 int /*<<< orphan*/  NFC_CMD_LLC_GET_PARAMS ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_genl_family ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfc_genl_send_params(struct sk_buff *msg,
				struct nfc_llcp_local *local,
				u32 portid, u32 seq)
{
	void *hdr;

	hdr = genlmsg_put(msg, portid, seq, &nfc_genl_family, 0,
			  NFC_CMD_LLC_GET_PARAMS);
	if (!hdr)
		return -EMSGSIZE;

	if (nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, local->dev->idx) ||
	    nla_put_u8(msg, NFC_ATTR_LLC_PARAM_LTO, local->lto) ||
	    nla_put_u8(msg, NFC_ATTR_LLC_PARAM_RW, local->rw) ||
	    nla_put_u16(msg, NFC_ATTR_LLC_PARAM_MIUX, be16_to_cpu(local->miux)))
		goto nla_put_failure;

	genlmsg_end(msg, hdr);
	return 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}