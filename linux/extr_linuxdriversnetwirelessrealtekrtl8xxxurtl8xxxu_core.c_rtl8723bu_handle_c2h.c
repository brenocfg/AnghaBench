#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; scalar_t__ data; } ;
struct rtl8xxxu_priv {TYPE_1__* udev; } ;
struct TYPE_10__ {int /*<<< orphan*/  payload; } ;
struct TYPE_9__ {int rate; int macid; int /*<<< orphan*/  noisy_state; int /*<<< orphan*/  dummy0_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  status; int /*<<< orphan*/  ext_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx_rx_mask; int /*<<< orphan*/  bt_has_reset; int /*<<< orphan*/  response_source; } ;
struct rtl8723bu_c2h {int id; TYPE_5__ raw; int /*<<< orphan*/  seq; TYPE_4__ ra_report; TYPE_3__ bt_mp_info; TYPE_2__ bt_info; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_INFO_SRC_8723B_BT_ACTIVE_SEND ; 
#define  C2H_8723B_BT_INFO 130 
#define  C2H_8723B_BT_MP_INFO 129 
#define  C2H_8723B_RA_REPORT 128 
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtl8723bu_handle_c2h(struct rtl8xxxu_priv *priv,
				 struct sk_buff *skb)
{
	struct rtl8723bu_c2h *c2h = (struct rtl8723bu_c2h *)skb->data;
	struct device *dev = &priv->udev->dev;
	int len;

	len = skb->len - 2;

	dev_dbg(dev, "C2H ID %02x seq %02x, len %02x source %02x\n",
		c2h->id, c2h->seq, len, c2h->bt_info.response_source);

	switch(c2h->id) {
	case C2H_8723B_BT_INFO:
		if (c2h->bt_info.response_source >
		    BT_INFO_SRC_8723B_BT_ACTIVE_SEND)
			dev_dbg(dev, "C2H_BT_INFO WiFi only firmware\n");
		else
			dev_dbg(dev, "C2H_BT_INFO BT/WiFi coexist firmware\n");

		if (c2h->bt_info.bt_has_reset)
			dev_dbg(dev, "BT has been reset\n");
		if (c2h->bt_info.tx_rx_mask)
			dev_dbg(dev, "BT TRx mask\n");

		break;
	case C2H_8723B_BT_MP_INFO:
		dev_dbg(dev, "C2H_MP_INFO ext ID %02x, status %02x\n",
			c2h->bt_mp_info.ext_id, c2h->bt_mp_info.status);
		break;
	case C2H_8723B_RA_REPORT:
		dev_dbg(dev,
			"C2H RA RPT: rate %02x, unk %i, macid %02x, noise %i\n",
			c2h->ra_report.rate, c2h->ra_report.dummy0_0,
			c2h->ra_report.macid, c2h->ra_report.noisy_state);
		break;
	default:
		dev_info(dev, "Unhandled C2H event %02x seq %02x\n",
			 c2h->id, c2h->seq);
		print_hex_dump(KERN_INFO, "C2H content: ", DUMP_PREFIX_NONE,
			       16, 1, c2h->raw.payload, len, false);
		break;
	}
}