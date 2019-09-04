#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct efx_nic {int wanted_fc; int /*<<< orphan*/  link_advertising; } ;

/* Variables and functions */
 int EFX_FC_RX ; 
 int EFX_FC_TX ; 
 int /*<<< orphan*/  __ETHTOOL_LINK_MODE_MASK_NBITS ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void efx_link_clear_advertising(struct efx_nic *efx)
{
	bitmap_zero(efx->link_advertising, __ETHTOOL_LINK_MODE_MASK_NBITS);
	efx->wanted_fc &= ~(EFX_FC_TX | EFX_FC_RX);
}