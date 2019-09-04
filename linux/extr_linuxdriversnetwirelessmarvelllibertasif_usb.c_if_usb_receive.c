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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int u32 ;
struct urb {int actual_length; int status; struct if_usb_card* context; } ;
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct lbs_private {int dummy; } ;
struct if_usb_card {TYPE_1__* udev; struct lbs_private* priv; struct sk_buff* rx_skb; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CMD_TYPE_DATA 130 
#define  CMD_TYPE_INDICATION 129 
#define  CMD_TYPE_REQUEST 128 
 int IPFIELD_ALIGN_OFFSET ; 
 int /*<<< orphan*/  if_usb_submit_rx_urb (struct if_usb_card*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lbs_deb_usbd (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  lbs_queue_event (struct lbs_private*,int) ; 
 int /*<<< orphan*/  lbs_send_tx_feedback (struct lbs_private*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_cmdrequest (int,int /*<<< orphan*/ *,struct sk_buff*,struct if_usb_card*,struct lbs_private*) ; 
 int /*<<< orphan*/  process_cmdtypedata (int,struct sk_buff*,struct if_usb_card*,struct lbs_private*) ; 

__attribute__((used)) static void if_usb_receive(struct urb *urb)
{
	struct if_usb_card *cardp = urb->context;
	struct sk_buff *skb = cardp->rx_skb;
	struct lbs_private *priv = cardp->priv;
	int recvlength = urb->actual_length;
	uint8_t *recvbuff = NULL;
	uint32_t recvtype = 0;
	__le32 *pkt = (__le32 *)(skb->data + IPFIELD_ALIGN_OFFSET);
	uint32_t event;

	if (recvlength) {
		if (urb->status) {
			lbs_deb_usbd(&cardp->udev->dev, "RX URB failed: %d\n",
				     urb->status);
			kfree_skb(skb);
			goto setup_for_next;
		}

		recvbuff = skb->data + IPFIELD_ALIGN_OFFSET;
		recvtype = le32_to_cpu(pkt[0]);
		lbs_deb_usbd(&cardp->udev->dev,
			    "Recv length = 0x%x, Recv type = 0x%X\n",
			    recvlength, recvtype);
	} else if (urb->status) {
		kfree_skb(skb);
		return;
	}

	switch (recvtype) {
	case CMD_TYPE_DATA:
		process_cmdtypedata(recvlength, skb, cardp, priv);
		break;

	case CMD_TYPE_REQUEST:
		process_cmdrequest(recvlength, recvbuff, skb, cardp, priv);
		break;

	case CMD_TYPE_INDICATION:
		/* Event handling */
		event = le32_to_cpu(pkt[1]);
		lbs_deb_usbd(&cardp->udev->dev, "**EVENT** 0x%X\n", event);
		kfree_skb(skb);

		/* Icky undocumented magic special case */
		if (event & 0xffff0000) {
			u32 trycount = (event & 0xffff0000) >> 16;

			lbs_send_tx_feedback(priv, trycount);
		} else
			lbs_queue_event(priv, event & 0xFF);
		break;

	default:
		lbs_deb_usbd(&cardp->udev->dev, "Unknown command type 0x%X\n",
			     recvtype);
		kfree_skb(skb);
		break;
	}

setup_for_next:
	if_usb_submit_rx_urb(cardp);
}