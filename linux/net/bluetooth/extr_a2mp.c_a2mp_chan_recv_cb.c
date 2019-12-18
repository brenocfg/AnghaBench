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
typedef  int u16 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct l2cap_chan {struct amp_mgr* data; } ;
struct amp_mgr {int /*<<< orphan*/  ident; } ;
struct a2mp_cmd_rej {int /*<<< orphan*/  reason; } ;
struct a2mp_cmd {int code; int /*<<< orphan*/  ident; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  rej ;

/* Variables and functions */
#define  A2MP_CHANGE_NOTIFY 140 
#define  A2MP_CHANGE_RSP 139 
#define  A2MP_COMMAND_REJ 138 
#define  A2MP_CREATEPHYSLINK_REQ 137 
#define  A2MP_CREATEPHYSLINK_RSP 136 
#define  A2MP_DISCONNPHYSLINK_REQ 135 
#define  A2MP_DISCONNPHYSLINK_RSP 134 
#define  A2MP_DISCOVER_REQ 133 
#define  A2MP_DISCOVER_RSP 132 
#define  A2MP_GETAMPASSOC_REQ 131 
#define  A2MP_GETAMPASSOC_RSP 130 
#define  A2MP_GETINFO_REQ 129 
#define  A2MP_GETINFO_RSP 128 
 int /*<<< orphan*/  BT_DBG (char*,int,int,...) ; 
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
 int EINVAL ; 
 int a2mp_change_notify (struct amp_mgr*,struct sk_buff*,struct a2mp_cmd*) ; 
 int a2mp_cmd_rsp (struct amp_mgr*,struct sk_buff*,struct a2mp_cmd*) ; 
 int /*<<< orphan*/  a2mp_command_rej (struct amp_mgr*,struct sk_buff*,struct a2mp_cmd*) ; 
 int a2mp_createphyslink_req (struct amp_mgr*,struct sk_buff*,struct a2mp_cmd*) ; 
 int a2mp_discover_req (struct amp_mgr*,struct sk_buff*,struct a2mp_cmd*) ; 
 int a2mp_discover_rsp (struct amp_mgr*,struct sk_buff*,struct a2mp_cmd*) ; 
 int a2mp_discphyslink_req (struct amp_mgr*,struct sk_buff*,struct a2mp_cmd*) ; 
 int a2mp_getampassoc_req (struct amp_mgr*,struct sk_buff*,struct a2mp_cmd*) ; 
 int a2mp_getampassoc_rsp (struct amp_mgr*,struct sk_buff*,struct a2mp_cmd*) ; 
 int a2mp_getinfo_req (struct amp_mgr*,struct sk_buff*,struct a2mp_cmd*) ; 
 int a2mp_getinfo_rsp (struct amp_mgr*,struct sk_buff*,struct a2mp_cmd*) ; 
 int /*<<< orphan*/  a2mp_send (struct amp_mgr*,int const,int /*<<< orphan*/ ,int,struct a2mp_cmd_rej*) ; 
 int /*<<< orphan*/  amp_mgr_get (struct amp_mgr*) ; 
 int /*<<< orphan*/  amp_mgr_put (struct amp_mgr*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int a2mp_chan_recv_cb(struct l2cap_chan *chan, struct sk_buff *skb)
{
	struct a2mp_cmd *hdr;
	struct amp_mgr *mgr = chan->data;
	int err = 0;

	amp_mgr_get(mgr);

	while (skb->len >= sizeof(*hdr)) {
		u16 len;

		hdr = (void *) skb->data;
		len = le16_to_cpu(hdr->len);

		BT_DBG("code 0x%2.2x id %d len %u", hdr->code, hdr->ident, len);

		skb_pull(skb, sizeof(*hdr));

		if (len > skb->len || !hdr->ident) {
			err = -EINVAL;
			break;
		}

		mgr->ident = hdr->ident;

		switch (hdr->code) {
		case A2MP_COMMAND_REJ:
			a2mp_command_rej(mgr, skb, hdr);
			break;

		case A2MP_DISCOVER_REQ:
			err = a2mp_discover_req(mgr, skb, hdr);
			break;

		case A2MP_CHANGE_NOTIFY:
			err = a2mp_change_notify(mgr, skb, hdr);
			break;

		case A2MP_GETINFO_REQ:
			err = a2mp_getinfo_req(mgr, skb, hdr);
			break;

		case A2MP_GETAMPASSOC_REQ:
			err = a2mp_getampassoc_req(mgr, skb, hdr);
			break;

		case A2MP_CREATEPHYSLINK_REQ:
			err = a2mp_createphyslink_req(mgr, skb, hdr);
			break;

		case A2MP_DISCONNPHYSLINK_REQ:
			err = a2mp_discphyslink_req(mgr, skb, hdr);
			break;

		case A2MP_DISCOVER_RSP:
			err = a2mp_discover_rsp(mgr, skb, hdr);
			break;

		case A2MP_GETINFO_RSP:
			err = a2mp_getinfo_rsp(mgr, skb, hdr);
			break;

		case A2MP_GETAMPASSOC_RSP:
			err = a2mp_getampassoc_rsp(mgr, skb, hdr);
			break;

		case A2MP_CHANGE_RSP:
		case A2MP_CREATEPHYSLINK_RSP:
		case A2MP_DISCONNPHYSLINK_RSP:
			err = a2mp_cmd_rsp(mgr, skb, hdr);
			break;

		default:
			BT_ERR("Unknown A2MP sig cmd 0x%2.2x", hdr->code);
			err = -EINVAL;
			break;
		}
	}

	if (err) {
		struct a2mp_cmd_rej rej;

		rej.reason = cpu_to_le16(0);
		hdr = (void *) skb->data;

		BT_DBG("Send A2MP Rej: cmd 0x%2.2x err %d", hdr->code, err);

		a2mp_send(mgr, A2MP_COMMAND_REJ, hdr->ident, sizeof(rej),
			  &rej);
	}

	/* Always free skb and return success error code to prevent
	   from sending L2CAP Disconnect over A2MP channel */
	kfree_skb(skb);

	amp_mgr_put(mgr);

	return 0;
}