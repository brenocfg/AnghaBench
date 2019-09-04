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
struct ef4_nic {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int MDIO45_RESET_ITERS ; 
 int MDIO45_RESET_TIME ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 int MDIO_CTRL1_RESET ; 
 int ef4_mdio_read (struct ef4_nic*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  msleep (int const) ; 
 int /*<<< orphan*/  netif_err (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int ef4_mdio_wait_reset_mmds(struct ef4_nic *efx, unsigned int mmd_mask)
{
	const int spintime = MDIO45_RESET_TIME / MDIO45_RESET_ITERS;
	int tries = MDIO45_RESET_ITERS;
	int rc = 0;
	int in_reset;

	while (tries) {
		int mask = mmd_mask;
		int mmd = 0;
		int stat;
		in_reset = 0;
		while (mask) {
			if (mask & 1) {
				stat = ef4_mdio_read(efx, mmd, MDIO_CTRL1);
				if (stat < 0) {
					netif_err(efx, hw, efx->net_dev,
						  "failed to read status of"
						  " MMD %d\n", mmd);
					return -EIO;
				}
				if (stat & MDIO_CTRL1_RESET)
					in_reset |= (1 << mmd);
			}
			mask = mask >> 1;
			mmd++;
		}
		if (!in_reset)
			break;
		tries--;
		msleep(spintime);
	}
	if (in_reset != 0) {
		netif_err(efx, hw, efx->net_dev,
			  "not all MMDs came out of reset in time."
			  " MMDs still in reset: %x\n", in_reset);
		rc = -ETIMEDOUT;
	}
	return rc;
}