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
struct txc43128_data {int /*<<< orphan*/  phy_mode; } ;
struct TYPE_2__ {int mode_support; int /*<<< orphan*/  mmds; } ;
struct ef4_nic {int loopback_modes; TYPE_1__ mdio; int /*<<< orphan*/  phy_mode; struct txc43128_data* phy_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FALCON_XMAC_LOOPBACKS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MDIO_EMULATE_C22 ; 
 int MDIO_SUPPORTS_C45 ; 
 int TXC_LOOPBACKS ; 
 int /*<<< orphan*/  TXC_REQUIRED_DEVS ; 
 struct txc43128_data* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int txc43128_phy_probe(struct ef4_nic *efx)
{
	struct txc43128_data *phy_data;

	/* Allocate phy private storage */
	phy_data = kzalloc(sizeof(*phy_data), GFP_KERNEL);
	if (!phy_data)
		return -ENOMEM;
	efx->phy_data = phy_data;
	phy_data->phy_mode = efx->phy_mode;

	efx->mdio.mmds = TXC_REQUIRED_DEVS;
	efx->mdio.mode_support = MDIO_SUPPORTS_C45 | MDIO_EMULATE_C22;

	efx->loopback_modes = TXC_LOOPBACKS | FALCON_XMAC_LOOPBACKS;

	return 0;
}