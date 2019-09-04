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
typedef  size_t u32 ;
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {struct mwifiex_pcie_card_reg* reg; } ;
struct pcie_service_card {size_t evtbd_rdptr; struct mwifiex_evt_buf_desc** evtbd_ring; struct sk_buff** evt_buf_list; TYPE_1__ pcie; } ;
struct mwifiex_pcie_card_reg {size_t evt_rollover_ind; int /*<<< orphan*/  evt_wrptr; } ;
struct mwifiex_evt_buf_desc {int dummy; } ;
struct mwifiex_adapter {int event_received; size_t intf_hdr_len; size_t event_cause; struct sk_buff* event_skb; int /*<<< orphan*/ * event_body; struct pcie_service_card* card; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_INTR_EVENT_DONE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EVENT ; 
 int /*<<< orphan*/  INFO ; 
 int MAX_EVENT_SIZE ; 
 int MWIFIEX_EVENT_HEADER_LEN ; 
 size_t MWIFIEX_EVTBD_MASK ; 
 size_t MWIFIEX_MAX_EVT_BD ; 
 int /*<<< orphan*/  PCIE_CPU_INT_EVENT ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 size_t get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct mwifiex_evt_buf_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mwifiex_pcie_ok_to_access_hw (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_pm_wakeup_card (struct mwifiex_adapter*) ; 
 scalar_t__ mwifiex_read_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  mwifiex_unmap_pci_memory (struct mwifiex_adapter*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ mwifiex_write_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

__attribute__((used)) static int mwifiex_pcie_process_event_ready(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;
	const struct mwifiex_pcie_card_reg *reg = card->pcie.reg;
	u32 rdptr = card->evtbd_rdptr & MWIFIEX_EVTBD_MASK;
	u32 wrptr, event;
	struct mwifiex_evt_buf_desc *desc;

	if (!mwifiex_pcie_ok_to_access_hw(adapter))
		mwifiex_pm_wakeup_card(adapter);

	if (adapter->event_received) {
		mwifiex_dbg(adapter, EVENT,
			    "info: Event being processed,\t"
			    "do not process this interrupt just yet\n");
		return 0;
	}

	if (rdptr >= MWIFIEX_MAX_EVT_BD) {
		mwifiex_dbg(adapter, ERROR,
			    "info: Invalid read pointer...\n");
		return -1;
	}

	/* Read the event ring write pointer set by firmware */
	if (mwifiex_read_reg(adapter, reg->evt_wrptr, &wrptr)) {
		mwifiex_dbg(adapter, ERROR,
			    "EventReady: failed to read reg->evt_wrptr\n");
		return -1;
	}

	mwifiex_dbg(adapter, EVENT,
		    "info: EventReady: Initial <Rd: 0x%x, Wr: 0x%x>",
		    card->evtbd_rdptr, wrptr);
	if (((wrptr & MWIFIEX_EVTBD_MASK) != (card->evtbd_rdptr
					      & MWIFIEX_EVTBD_MASK)) ||
	    ((wrptr & reg->evt_rollover_ind) ==
	     (card->evtbd_rdptr & reg->evt_rollover_ind))) {
		struct sk_buff *skb_cmd;
		__le16 data_len = 0;
		u16 evt_len;

		mwifiex_dbg(adapter, INFO,
			    "info: Read Index: %d\n", rdptr);
		skb_cmd = card->evt_buf_list[rdptr];
		mwifiex_unmap_pci_memory(adapter, skb_cmd, PCI_DMA_FROMDEVICE);

		/* Take the pointer and set it to event pointer in adapter
		   and will return back after event handling callback */
		card->evt_buf_list[rdptr] = NULL;
		desc = card->evtbd_ring[rdptr];
		memset(desc, 0, sizeof(*desc));

		event = get_unaligned_le32(
			&skb_cmd->data[adapter->intf_hdr_len]);
		adapter->event_cause = event;
		/* The first 4bytes will be the event transfer header
		   len is 2 bytes followed by type which is 2 bytes */
		memcpy(&data_len, skb_cmd->data, sizeof(__le16));
		evt_len = le16_to_cpu(data_len);
		skb_trim(skb_cmd, evt_len);
		skb_pull(skb_cmd, adapter->intf_hdr_len);
		mwifiex_dbg(adapter, EVENT,
			    "info: Event length: %d\n", evt_len);

		if (evt_len > MWIFIEX_EVENT_HEADER_LEN &&
		    evt_len < MAX_EVENT_SIZE)
			memcpy(adapter->event_body, skb_cmd->data +
			       MWIFIEX_EVENT_HEADER_LEN, evt_len -
			       MWIFIEX_EVENT_HEADER_LEN);

		adapter->event_received = true;
		adapter->event_skb = skb_cmd;

		/* Do not update the event read pointer here, wait till the
		   buffer is released. This is just to make things simpler,
		   we need to find a better method of managing these buffers.
		*/
	} else {
		if (mwifiex_write_reg(adapter, PCIE_CPU_INT_EVENT,
				      CPU_INTR_EVENT_DONE)) {
			mwifiex_dbg(adapter, ERROR,
				    "Write register failed\n");
			return -1;
		}
	}

	return 0;
}