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
struct TYPE_3__ {struct mwifiex_pcie_card_reg* reg; } ;
struct pcie_service_card {int txbd_wrptr; TYPE_2__* dev; TYPE_1__ pcie; } ;
struct mwifiex_pcie_card_reg {int tx_mask; int tx_rollover_ind; } ;
struct TYPE_4__ {int device; } ;

/* Variables and functions */
#define  PCIE_DEVICE_ID_MARVELL_88W8766P 130 
#define  PCIE_DEVICE_ID_MARVELL_88W8897 129 
#define  PCIE_DEVICE_ID_MARVELL_88W8997 128 

__attribute__((used)) static inline int
mwifiex_pcie_txbd_empty(struct pcie_service_card *card, u32 rdptr)
{
	const struct mwifiex_pcie_card_reg *reg = card->pcie.reg;

	switch (card->dev->device) {
	case PCIE_DEVICE_ID_MARVELL_88W8766P:
		if (((card->txbd_wrptr & reg->tx_mask) ==
		     (rdptr & reg->tx_mask)) &&
		    ((card->txbd_wrptr & reg->tx_rollover_ind) !=
		     (rdptr & reg->tx_rollover_ind)))
			return 1;
		break;
	case PCIE_DEVICE_ID_MARVELL_88W8897:
	case PCIE_DEVICE_ID_MARVELL_88W8997:
		if (((card->txbd_wrptr & reg->tx_mask) ==
		     (rdptr & reg->tx_mask)) &&
		    ((card->txbd_wrptr & reg->tx_rollover_ind) ==
			(rdptr & reg->tx_rollover_ind)))
			return 1;
		break;
	}

	return 0;
}