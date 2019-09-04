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
struct stmmac_priv {scalar_t__ synopsys_id; int extend_desc; int /*<<< orphan*/  device; TYPE_1__* plat; struct mac_device_info* hw; } ;
struct mac_device_info {int /*<<< orphan*/ * desc; } ;
struct TYPE_2__ {scalar_t__ enh_desc; } ;

/* Variables and functions */
 scalar_t__ DWMAC_CORE_3_50 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  enh_desc_ops ; 
 int /*<<< orphan*/  ndesc_ops ; 
 int /*<<< orphan*/  stmmac_dwmac_mode_quirk (struct stmmac_priv*) ; 

__attribute__((used)) static int stmmac_dwmac1_quirks(struct stmmac_priv *priv)
{
	struct mac_device_info *mac = priv->hw;

	if (priv->plat->enh_desc) {
		dev_info(priv->device, "Enhanced/Alternate descriptors\n");

		/* GMAC older than 3.50 has no extended descriptors */
		if (priv->synopsys_id >= DWMAC_CORE_3_50) {
			dev_info(priv->device, "Enabled extended descriptors\n");
			priv->extend_desc = 1;
		} else {
			dev_warn(priv->device, "Extended descriptors not supported\n");
		}

		mac->desc = &enh_desc_ops;
	} else {
		dev_info(priv->device, "Normal descriptors\n");
		mac->desc = &ndesc_ops;
	}

	stmmac_dwmac_mode_quirk(priv);
	return 0;
}