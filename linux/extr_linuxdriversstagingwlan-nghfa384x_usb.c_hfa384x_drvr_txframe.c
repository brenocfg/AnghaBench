#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union p80211_hdr {int dummy; } p80211_hdr ;
struct sk_buff {int len; union p80211_hdr* data; } ;
struct p80211_metawep {union p80211_hdr* icv; union p80211_hdr* data; union p80211_hdr* iv; } ;
struct hfa384x_tx_frame {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  status; } ;
struct TYPE_11__ {int sw_support; int tx_control; char frame_control; void* data_len; } ;
struct TYPE_7__ {char* data; TYPE_6__ desc; } ;
struct TYPE_9__ {TYPE_1__ txfrm; void* type; } ;
struct hfa384x {TYPE_4__* wlandev; TYPE_2__ tx_urb; TYPE_3__ txbuff; int /*<<< orphan*/  endp_out; int /*<<< orphan*/  usb; } ;
struct TYPE_10__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HFA384x_TX_MACPORT_SET (int /*<<< orphan*/ ) ; 
 int HFA384x_TX_STRUCTYPE_SET (int) ; 
 int HFA384x_TX_TXEX_SET (int /*<<< orphan*/ ) ; 
 int HFA384x_TX_TXOK_SET (int /*<<< orphan*/ ) ; 
 int HFA384x_USB_TXFRM ; 
 int /*<<< orphan*/  ROUNDUP64 (int) ; 
 int /*<<< orphan*/  USB_QUEUE_BULK ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le16s (int*) ; 
 int /*<<< orphan*/  hfa384x_usbout_callback ; 
 int /*<<< orphan*/  memcpy (char*,union p80211_hdr*,int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int submit_tx_urb (struct hfa384x*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 

int hfa384x_drvr_txframe(struct hfa384x *hw, struct sk_buff *skb,
			 union p80211_hdr *p80211_hdr,
			 struct p80211_metawep *p80211_wep)
{
	int usbpktlen = sizeof(struct hfa384x_tx_frame);
	int result;
	int ret;
	char *ptr;

	if (hw->tx_urb.status == -EINPROGRESS) {
		netdev_warn(hw->wlandev->netdev, "TX URB already in use\n");
		result = 3;
		goto exit;
	}

	/* Build Tx frame structure */
	/* Set up the control field */
	memset(&hw->txbuff.txfrm.desc, 0, sizeof(hw->txbuff.txfrm.desc));

	/* Setup the usb type field */
	hw->txbuff.type = cpu_to_le16(HFA384x_USB_TXFRM);

	/* Set up the sw_support field to identify this frame */
	hw->txbuff.txfrm.desc.sw_support = 0x0123;

/* Tx complete and Tx exception disable per dleach.  Might be causing
 * buf depletion
 */
/* #define DOEXC  SLP -- doboth breaks horribly under load, doexc less so. */
#if defined(DOBOTH)
	hw->txbuff.txfrm.desc.tx_control =
	    HFA384x_TX_MACPORT_SET(0) | HFA384x_TX_STRUCTYPE_SET(1) |
	    HFA384x_TX_TXEX_SET(1) | HFA384x_TX_TXOK_SET(1);
#elif defined(DOEXC)
	hw->txbuff.txfrm.desc.tx_control =
	    HFA384x_TX_MACPORT_SET(0) | HFA384x_TX_STRUCTYPE_SET(1) |
	    HFA384x_TX_TXEX_SET(1) | HFA384x_TX_TXOK_SET(0);
#else
	hw->txbuff.txfrm.desc.tx_control =
	    HFA384x_TX_MACPORT_SET(0) | HFA384x_TX_STRUCTYPE_SET(1) |
	    HFA384x_TX_TXEX_SET(0) | HFA384x_TX_TXOK_SET(0);
#endif
	cpu_to_le16s(&hw->txbuff.txfrm.desc.tx_control);

	/* copy the header over to the txdesc */
	memcpy(&hw->txbuff.txfrm.desc.frame_control, p80211_hdr,
	       sizeof(union p80211_hdr));

	/* if we're using host WEP, increase size by IV+ICV */
	if (p80211_wep->data) {
		hw->txbuff.txfrm.desc.data_len = cpu_to_le16(skb->len + 8);
		usbpktlen += 8;
	} else {
		hw->txbuff.txfrm.desc.data_len = cpu_to_le16(skb->len);
	}

	usbpktlen += skb->len;

	/* copy over the WEP IV if we are using host WEP */
	ptr = hw->txbuff.txfrm.data;
	if (p80211_wep->data) {
		memcpy(ptr, p80211_wep->iv, sizeof(p80211_wep->iv));
		ptr += sizeof(p80211_wep->iv);
		memcpy(ptr, p80211_wep->data, skb->len);
	} else {
		memcpy(ptr, skb->data, skb->len);
	}
	/* copy over the packet data */
	ptr += skb->len;

	/* copy over the WEP ICV if we are using host WEP */
	if (p80211_wep->data)
		memcpy(ptr, p80211_wep->icv, sizeof(p80211_wep->icv));

	/* Send the USB packet */
	usb_fill_bulk_urb(&hw->tx_urb, hw->usb,
			  hw->endp_out,
			  &hw->txbuff, ROUNDUP64(usbpktlen),
			  hfa384x_usbout_callback, hw->wlandev);
	hw->tx_urb.transfer_flags |= USB_QUEUE_BULK;

	result = 1;
	ret = submit_tx_urb(hw, &hw->tx_urb, GFP_ATOMIC);
	if (ret != 0) {
		netdev_err(hw->wlandev->netdev,
			   "submit_tx_urb() failed, error=%d\n", ret);
		result = 3;
	}

exit:
	return result;
}