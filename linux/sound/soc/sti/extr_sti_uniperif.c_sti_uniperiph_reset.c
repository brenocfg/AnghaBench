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
struct uniperif {scalar_t__ ver; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ GET_UNIPERIF_SOFT_RST_SOFT_RST (struct uniperif*) ; 
 int /*<<< orphan*/  SET_UNIPERIF_SOFT_RST_SOFT_RST (struct uniperif*) ; 
 scalar_t__ SND_ST_UNIPERIF_VERSION_UNI_PLR_TOP_1_0 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

int  sti_uniperiph_reset(struct uniperif *uni)
{
	int count = 10;

	/* Reset uniperipheral uni */
	SET_UNIPERIF_SOFT_RST_SOFT_RST(uni);

	if (uni->ver < SND_ST_UNIPERIF_VERSION_UNI_PLR_TOP_1_0) {
		while (GET_UNIPERIF_SOFT_RST_SOFT_RST(uni) && count) {
			udelay(5);
			count--;
		}
	}

	if (!count) {
		dev_err(uni->dev, "Failed to reset uniperif\n");
		return -EIO;
	}

	return 0;
}