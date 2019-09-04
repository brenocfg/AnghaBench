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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct mwifiex_rxinfo {int bss_num; int bss_type; } ;
struct mwifiex_private {int bss_num; int bss_type; scalar_t__ bss_role; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* event_complete ) (struct mwifiex_adapter*,struct sk_buff*) ;} ;
struct TYPE_3__ {int last_event_index; scalar_t__* last_event; } ;
struct mwifiex_adapter {int event_cause; int priv_num; TYPE_2__ if_ops; struct sk_buff* event_skb; TYPE_1__ dbg; struct mwifiex_private** priv; } ;

/* Variables and functions */
 int DBG_CMD_NUM ; 
 int /*<<< orphan*/  EVENT ; 
 int /*<<< orphan*/  EVENT_GET_BSS_NUM (int) ; 
 int /*<<< orphan*/  EVENT_GET_BSS_TYPE (int) ; 
 int EVENT_ID_MASK ; 
 int EVENT_RADAR_DETECTED ; 
 int /*<<< orphan*/  EVT_D ; 
 int /*<<< orphan*/  MWIFIEX_BSS_ROLE_ANY ; 
 scalar_t__ MWIFIEX_BSS_ROLE_UAP ; 
 struct mwifiex_rxinfo* MWIFIEX_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct mwifiex_rxinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mwifiex_dbg_dump (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mwifiex_private* mwifiex_get_priv (struct mwifiex_adapter*,int /*<<< orphan*/ ) ; 
 struct mwifiex_private* mwifiex_get_priv_by_id (struct mwifiex_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mwifiex_is_11h_active (struct mwifiex_private*) ; 
 int mwifiex_process_sta_event (struct mwifiex_private*) ; 
 int mwifiex_process_uap_event (struct mwifiex_private*) ; 
 int /*<<< orphan*/  stub1 (struct mwifiex_adapter*,struct sk_buff*) ; 

int mwifiex_process_event(struct mwifiex_adapter *adapter)
{
	int ret, i;
	struct mwifiex_private *priv =
		mwifiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);
	struct sk_buff *skb = adapter->event_skb;
	u32 eventcause;
	struct mwifiex_rxinfo *rx_info;

	if ((adapter->event_cause & EVENT_ID_MASK) == EVENT_RADAR_DETECTED) {
		for (i = 0; i < adapter->priv_num; i++) {
			priv = adapter->priv[i];
			if (priv && mwifiex_is_11h_active(priv)) {
				adapter->event_cause |=
					((priv->bss_num & 0xff) << 16) |
					((priv->bss_type & 0xff) << 24);
				break;
			}
		}
	}

	eventcause = adapter->event_cause;

	/* Save the last event to debug log */
	adapter->dbg.last_event_index =
			(adapter->dbg.last_event_index + 1) % DBG_CMD_NUM;
	adapter->dbg.last_event[adapter->dbg.last_event_index] =
							(u16) eventcause;

	/* Get BSS number and corresponding priv */
	priv = mwifiex_get_priv_by_id(adapter, EVENT_GET_BSS_NUM(eventcause),
				      EVENT_GET_BSS_TYPE(eventcause));
	if (!priv)
		priv = mwifiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);

	/* Clear BSS_NO_BITS from event */
	eventcause &= EVENT_ID_MASK;
	adapter->event_cause = eventcause;

	if (skb) {
		rx_info = MWIFIEX_SKB_RXCB(skb);
		memset(rx_info, 0, sizeof(*rx_info));
		rx_info->bss_num = priv->bss_num;
		rx_info->bss_type = priv->bss_type;
		mwifiex_dbg_dump(adapter, EVT_D, "Event Buf:",
				 skb->data, skb->len);
	}

	mwifiex_dbg(adapter, EVENT, "EVENT: cause: %#x\n", eventcause);

	if (priv->bss_role == MWIFIEX_BSS_ROLE_UAP)
		ret = mwifiex_process_uap_event(priv);
	else
		ret = mwifiex_process_sta_event(priv);

	adapter->event_cause = 0;
	adapter->event_skb = NULL;
	adapter->if_ops.event_complete(adapter, skb);

	return ret;
}