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
typedef  int u16 ;
struct TYPE_4__ {scalar_t__ rfpwr_state; } ;
struct rtl_priv {TYPE_2__ psc; } ;
struct TYPE_3__ {struct rtl8192_tx_ring* tx_ring; } ;
struct rtl_pci_priv {TYPE_1__ dev; } ;
struct rtl_mac {scalar_t__ skip_scan; } ;
struct rtl_hal {int dummy; } ;
struct rtl8192_tx_ring {int /*<<< orphan*/  queue; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BEACON_QUEUE ; 
 scalar_t__ ERFOFF ; 
 int RTL_PCI_MAX_TX_QUEUE_COUNT ; 
 int TXCMD_QUEUE ; 
 scalar_t__ is_hal_stop (struct rtl_hal*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_pci_priv* rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl_pci_flush(struct ieee80211_hw *hw, u32 queues, bool drop)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 i = 0;
	int queue_id;
	struct rtl8192_tx_ring *ring;

	if (mac->skip_scan)
		return;

	for (queue_id = RTL_PCI_MAX_TX_QUEUE_COUNT - 1; queue_id >= 0;) {
		u32 queue_len;

		if (((queues >> queue_id) & 0x1) == 0) {
			queue_id--;
			continue;
		}
		ring = &pcipriv->dev.tx_ring[queue_id];
		queue_len = skb_queue_len(&ring->queue);
		if (queue_len == 0 || queue_id == BEACON_QUEUE ||
		    queue_id == TXCMD_QUEUE) {
			queue_id--;
			continue;
		} else {
			msleep(20);
			i++;
		}

		/* we just wait 1s for all queues */
		if (rtlpriv->psc.rfpwr_state == ERFOFF ||
		    is_hal_stop(rtlhal) || i >= 200)
			return;
	}
}