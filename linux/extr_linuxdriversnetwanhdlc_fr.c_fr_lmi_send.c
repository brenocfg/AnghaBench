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
typedef  int u8 ;
struct sk_buff {struct net_device* dev; int /*<<< orphan*/  priority; void* protocol; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int exist; int new; int active; } ;
struct pvc_device {int dlci; struct pvc_device* next; TYPE_2__ state; scalar_t__ open_count; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  hdlc_device ;
struct TYPE_4__ {int lmi; int dce; } ;
struct TYPE_6__ {int dce_pvc_count; int txseq; int rxseq; scalar_t__ reliable; TYPE_1__ settings; struct pvc_device* first_pvc; } ;

/* Variables and functions */
 int HDLC_MAX_MRU ; 
 int LMI_ANSI ; 
 int LMI_ANSI_CISCO_ALIVE ; 
 int LMI_ANSI_CISCO_PVCSTAT ; 
 int LMI_ANSI_CISCO_REPTYPE ; 
 int LMI_ANSI_LENGTH ; 
 int LMI_ANSI_LOCKSHIFT ; 
 int LMI_CALLREF ; 
 int LMI_CCITT ; 
 int LMI_CCITT_ALIVE ; 
 int /*<<< orphan*/  LMI_CCITT_ANSI_DLCI ; 
 int LMI_CCITT_CISCO_LENGTH ; 
 int LMI_CCITT_PVCSTAT ; 
 int LMI_CCITT_REPTYPE ; 
 int LMI_CISCO ; 
 int /*<<< orphan*/  LMI_CISCO_DLCI ; 
 int LMI_FULLREP ; 
 int LMI_INTEGRITY ; 
 int LMI_INTEG_LEN ; 
 int LMI_REPT_LEN ; 
 int LMI_STATUS ; 
 int LMI_STATUS_ENQUIRY ; 
 int /*<<< orphan*/  NLPID_CCITT_ANSI_LMI ; 
 int /*<<< orphan*/  NLPID_CISCO_LMI ; 
 int /*<<< orphan*/  TC_PRIO_CONTROL ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/ * dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  fr_hard_header (struct sk_buff**,int /*<<< orphan*/ ) ; 
 int fr_lmi_nextseq (int) ; 
 int /*<<< orphan*/  fr_log_dlci_active (struct pvc_device*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  pvc_carrier (int,struct pvc_device*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int* skb_tail_pointer (struct sk_buff*) ; 
 TYPE_3__* state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fr_lmi_send(struct net_device *dev, int fullrep)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);
	struct sk_buff *skb;
	struct pvc_device *pvc = state(hdlc)->first_pvc;
	int lmi = state(hdlc)->settings.lmi;
	int dce = state(hdlc)->settings.dce;
	int len = lmi == LMI_ANSI ? LMI_ANSI_LENGTH : LMI_CCITT_CISCO_LENGTH;
	int stat_len = (lmi == LMI_CISCO) ? 6 : 3;
	u8 *data;
	int i = 0;

	if (dce && fullrep) {
		len += state(hdlc)->dce_pvc_count * (2 + stat_len);
		if (len > HDLC_MAX_MRU) {
			netdev_warn(dev, "Too many PVCs while sending LMI full report\n");
			return;
		}
	}

	skb = dev_alloc_skb(len);
	if (!skb) {
		netdev_warn(dev, "Memory squeeze on fr_lmi_send()\n");
		return;
	}
	memset(skb->data, 0, len);
	skb_reserve(skb, 4);
	if (lmi == LMI_CISCO) {
		skb->protocol = cpu_to_be16(NLPID_CISCO_LMI);
		fr_hard_header(&skb, LMI_CISCO_DLCI);
	} else {
		skb->protocol = cpu_to_be16(NLPID_CCITT_ANSI_LMI);
		fr_hard_header(&skb, LMI_CCITT_ANSI_DLCI);
	}
	data = skb_tail_pointer(skb);
	data[i++] = LMI_CALLREF;
	data[i++] = dce ? LMI_STATUS : LMI_STATUS_ENQUIRY;
	if (lmi == LMI_ANSI)
		data[i++] = LMI_ANSI_LOCKSHIFT;
	data[i++] = lmi == LMI_CCITT ? LMI_CCITT_REPTYPE :
		LMI_ANSI_CISCO_REPTYPE;
	data[i++] = LMI_REPT_LEN;
	data[i++] = fullrep ? LMI_FULLREP : LMI_INTEGRITY;
	data[i++] = lmi == LMI_CCITT ? LMI_CCITT_ALIVE : LMI_ANSI_CISCO_ALIVE;
	data[i++] = LMI_INTEG_LEN;
	data[i++] = state(hdlc)->txseq =
		fr_lmi_nextseq(state(hdlc)->txseq);
	data[i++] = state(hdlc)->rxseq;

	if (dce && fullrep) {
		while (pvc) {
			data[i++] = lmi == LMI_CCITT ? LMI_CCITT_PVCSTAT :
				LMI_ANSI_CISCO_PVCSTAT;
			data[i++] = stat_len;

			/* LMI start/restart */
			if (state(hdlc)->reliable && !pvc->state.exist) {
				pvc->state.exist = pvc->state.new = 1;
				fr_log_dlci_active(pvc);
			}

			/* ifconfig PVC up */
			if (pvc->open_count && !pvc->state.active &&
			    pvc->state.exist && !pvc->state.new) {
				pvc_carrier(1, pvc);
				pvc->state.active = 1;
				fr_log_dlci_active(pvc);
			}

			if (lmi == LMI_CISCO) {
				data[i] = pvc->dlci >> 8;
				data[i + 1] = pvc->dlci & 0xFF;
			} else {
				data[i] = (pvc->dlci >> 4) & 0x3F;
				data[i + 1] = ((pvc->dlci << 3) & 0x78) | 0x80;
				data[i + 2] = 0x80;
			}

			if (pvc->state.new)
				data[i + 2] |= 0x08;
			else if (pvc->state.active)
				data[i + 2] |= 0x02;

			i += stat_len;
			pvc = pvc->next;
		}
	}

	skb_put(skb, i);
	skb->priority = TC_PRIO_CONTROL;
	skb->dev = dev;
	skb_reset_network_header(skb);

	dev_queue_xmit(skb);
}