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
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 int /*<<< orphan*/  TXC_BIST_CTRL_TYPE_TSD ; 
 int txc_bist_one (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int txc_bist(struct ef4_nic *efx)
{
	return txc_bist_one(efx, MDIO_MMD_PCS, TXC_BIST_CTRL_TYPE_TSD);
}