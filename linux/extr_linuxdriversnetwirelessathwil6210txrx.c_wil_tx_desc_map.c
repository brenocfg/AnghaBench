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
struct TYPE_4__ {int* d; scalar_t__ ucode_cmd; } ;
struct TYPE_3__ {int d0; int /*<<< orphan*/  length; scalar_t__ status; scalar_t__ error; scalar_t__ b11; scalar_t__ ip_length; int /*<<< orphan*/  addr; } ;
struct vring_tx_desc {TYPE_2__ mac; TYPE_1__ dma; } ;
union wil_tx_desc {struct vring_tx_desc legacy; } ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int DMA_CFG_DESC_TX_0_QID_POS ; 
 int MAC_CFG_DESC_TX_2_L2_TRANSLATION_TYPE_POS ; 
 int /*<<< orphan*/  MAC_CFG_DESC_TX_2_SNAP_HDR_INSERTION_EN_POS ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_desc_addr_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wil_tx_desc_map(union wil_tx_desc *desc, dma_addr_t pa,
			   u32 len, int vring_index)
{
	struct vring_tx_desc *d = &desc->legacy;

	wil_desc_addr_set(&d->dma.addr, pa);
	d->dma.ip_length = 0;
	/* 0..6: mac_length; 7:ip_version 0-IP6 1-IP4*/
	d->dma.b11 = 0/*14 | BIT(7)*/;
	d->dma.error = 0;
	d->dma.status = 0; /* BIT(0) should be 0 for HW_OWNED */
	d->dma.length = cpu_to_le16((u16)len);
	d->dma.d0 = (vring_index << DMA_CFG_DESC_TX_0_QID_POS);
	d->mac.d[0] = 0;
	d->mac.d[1] = 0;
	d->mac.d[2] = 0;
	d->mac.ucode_cmd = 0;
	/* translation type:  0 - bypass; 1 - 802.3; 2 - native wifi */
	d->mac.d[2] = BIT(MAC_CFG_DESC_TX_2_SNAP_HDR_INSERTION_EN_POS) |
		      (1 << MAC_CFG_DESC_TX_2_L2_TRANSLATION_TYPE_POS);

	return 0;
}