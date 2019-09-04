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
struct TYPE_2__ {int* d; } ;
struct vring_tx_desc {TYPE_1__ mac; } ;

/* Variables and functions */
 int MAC_CFG_DESC_TX_2_NUM_OF_DESCRIPTORS_POS ; 

__attribute__((used)) static inline
void wil_tx_desc_set_nr_frags(struct vring_tx_desc *d, int nr_frags)
{
	d->mac.d[2] |= (nr_frags << MAC_CFG_DESC_TX_2_NUM_OF_DESCRIPTORS_POS);
}