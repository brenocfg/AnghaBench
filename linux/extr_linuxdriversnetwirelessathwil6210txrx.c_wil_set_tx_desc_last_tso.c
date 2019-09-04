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
struct TYPE_2__ {int d0; } ;
struct vring_tx_desc {TYPE_1__ dma; } ;

/* Variables and functions */
 int DMA_CFG_DESC_TX_0_SEGMENT_BUF_DETAILS_POS ; 
 int wil_tso_type_lst ; 

__attribute__((used)) static inline void wil_set_tx_desc_last_tso(volatile struct vring_tx_desc *d)
{
	d->dma.d0 |= wil_tso_type_lst <<
		  DMA_CFG_DESC_TX_0_SEGMENT_BUF_DETAILS_POS;
}