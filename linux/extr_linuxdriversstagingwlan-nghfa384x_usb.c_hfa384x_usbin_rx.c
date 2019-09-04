#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  status; scalar_t__ silence; scalar_t__ signal; int /*<<< orphan*/  rate; int /*<<< orphan*/  time; int /*<<< orphan*/  frame_control; int /*<<< orphan*/  data_len; } ;
struct TYPE_6__ {TYPE_2__ desc; } ;
union hfa384x_usbin {TYPE_3__ rxfrm; } ;
typedef  int /*<<< orphan*/  u16 ;
struct wlandevice {int hostwep; int /*<<< orphan*/  netdev; struct hfa384x* priv; } ;
struct sk_buff {int /*<<< orphan*/  dev; scalar_t__ data; } ;
struct p80211_rxmeta {scalar_t__ noise; scalar_t__ signal; int /*<<< orphan*/  rxrate; int /*<<< orphan*/  mactime; } ;
struct hfa384x_rx_frame {int dummy; } ;
struct hfa384x {TYPE_1__* wlandev; scalar_t__ dbmadjust; } ;
struct TYPE_4__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384x_RXSTATUS_ISFCSERR (int /*<<< orphan*/ ) ; 
 int HFA384x_RXSTATUS_MACPORT_GET (int /*<<< orphan*/ ) ; 
 int HOSTWEP_EXCLUDEUNENCRYPTED ; 
 int /*<<< orphan*/  WLAN_CRC_LEN ; 
 int /*<<< orphan*/  WLAN_GET_FC_ISWEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  hfa384x_int_rxmonitor (struct wlandevice*,TYPE_3__*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int p80211_headerlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p80211netdev_rx (struct wlandevice*,struct sk_buff*) ; 
 struct p80211_rxmeta* p80211skb_rxmeta (struct sk_buff*) ; 
 int /*<<< orphan*/  p80211skb_rxmeta_attach (struct wlandevice*,struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hfa384x_usbin_rx(struct wlandevice *wlandev, struct sk_buff *skb)
{
	union hfa384x_usbin *usbin = (union hfa384x_usbin *)skb->data;
	struct hfa384x *hw = wlandev->priv;
	int hdrlen;
	struct p80211_rxmeta *rxmeta;
	u16 data_len;
	u16 fc;

	/* Byte order convert once up front. */
	le16_to_cpus(&usbin->rxfrm.desc.status);
	le32_to_cpus(&usbin->rxfrm.desc.time);

	/* Now handle frame based on port# */
	switch (HFA384x_RXSTATUS_MACPORT_GET(usbin->rxfrm.desc.status)) {
	case 0:
		fc = le16_to_cpu(usbin->rxfrm.desc.frame_control);

		/* If exclude and we receive an unencrypted, drop it */
		if ((wlandev->hostwep & HOSTWEP_EXCLUDEUNENCRYPTED) &&
		    !WLAN_GET_FC_ISWEP(fc)) {
			break;
		}

		data_len = le16_to_cpu(usbin->rxfrm.desc.data_len);

		/* How much header data do we have? */
		hdrlen = p80211_headerlen(fc);

		/* Pull off the descriptor */
		skb_pull(skb, sizeof(struct hfa384x_rx_frame));

		/* Now shunt the header block up against the data block
		 * with an "overlapping" copy
		 */
		memmove(skb_push(skb, hdrlen),
			&usbin->rxfrm.desc.frame_control, hdrlen);

		skb->dev = wlandev->netdev;

		/* And set the frame length properly */
		skb_trim(skb, data_len + hdrlen);

		/* The prism2 series does not return the CRC */
		memset(skb_put(skb, WLAN_CRC_LEN), 0xff, WLAN_CRC_LEN);

		skb_reset_mac_header(skb);

		/* Attach the rxmeta, set some stuff */
		p80211skb_rxmeta_attach(wlandev, skb);
		rxmeta = p80211skb_rxmeta(skb);
		rxmeta->mactime = usbin->rxfrm.desc.time;
		rxmeta->rxrate = usbin->rxfrm.desc.rate;
		rxmeta->signal = usbin->rxfrm.desc.signal - hw->dbmadjust;
		rxmeta->noise = usbin->rxfrm.desc.silence - hw->dbmadjust;

		p80211netdev_rx(wlandev, skb);

		break;

	case 7:
		if (!HFA384x_RXSTATUS_ISFCSERR(usbin->rxfrm.desc.status)) {
			/* Copy to wlansnif skb */
			hfa384x_int_rxmonitor(wlandev, &usbin->rxfrm);
			dev_kfree_skb(skb);
		} else {
			pr_debug("Received monitor frame: FCSerr set\n");
		}
		break;

	default:
		netdev_warn(hw->wlandev->netdev, "Received frame on unsupported port=%d\n",
			    HFA384x_RXSTATUS_MACPORT_GET(usbin->rxfrm.desc.status));
		break;
	}
}