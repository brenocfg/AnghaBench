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
union wil_tx_desc {int /*<<< orphan*/  enhanced; } ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int* d; } ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  addr_high_high; int /*<<< orphan*/  addr; } ;
struct wil_tx_enhanced_desc {TYPE_2__ mac; TYPE_1__ dma; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int MAC_CFG_DESC_TX_2_L2_TRANSLATION_TYPE_POS ; 
 int /*<<< orphan*/  MAC_CFG_DESC_TX_2_SNAP_HDR_INSERTION_EN_POS ; 
 int WIL_EDMA_DESC_TX_MAC_CFG_0_QID_POS ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct wil_tx_enhanced_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wil_desc_set_addr_edma (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wil_tx_desc_map_edma(union wil_tx_desc *desc,
				dma_addr_t pa,
				u32 len,
				int ring_index)
{
	struct wil_tx_enhanced_desc *d =
		(struct wil_tx_enhanced_desc *)&desc->enhanced;

	memset(d, 0, sizeof(struct wil_tx_enhanced_desc));

	wil_desc_set_addr_edma(&d->dma.addr, &d->dma.addr_high_high, pa);

	/* 0..6: mac_length; 7:ip_version 0-IP6 1-IP4*/
	d->dma.length = cpu_to_le16((u16)len);
	d->mac.d[0] = (ring_index << WIL_EDMA_DESC_TX_MAC_CFG_0_QID_POS);
	/* translation type:  0 - bypass; 1 - 802.3; 2 - native wifi;
	 * 3 - eth mode
	 */
	d->mac.d[2] = BIT(MAC_CFG_DESC_TX_2_SNAP_HDR_INSERTION_EN_POS) |
		      (0x3 << MAC_CFG_DESC_TX_2_L2_TRANSLATION_TYPE_POS);

	return 0;
}