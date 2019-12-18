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
typedef  int u32 ;
struct fe_priv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FE_MDIO_ACCESS ; 
 int FE_MDIO_RETRY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int fe_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rt2880_mdio_wait_ready(struct fe_priv *priv)
{
	int retries;

	retries = FE_MDIO_RETRY;
	while (1) {
		u32 t;

		t = fe_r32(FE_MDIO_ACCESS);
		if ((t & BIT(31)) == 0)
			return 0;

		if (retries-- == 0)
			break;

		udelay(1);
	}

	dev_err(priv->dev, "MDIO operation timed out\n");
	return -ETIMEDOUT;
}