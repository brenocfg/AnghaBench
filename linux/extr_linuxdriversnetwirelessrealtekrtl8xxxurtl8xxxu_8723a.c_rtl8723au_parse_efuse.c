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
struct rtl8723au_efuse {scalar_t__ rtl_id; int version; int xtal_k; int /*<<< orphan*/  device_name; int /*<<< orphan*/  vendor_name; int /*<<< orphan*/  ht20_max_power_offset; int /*<<< orphan*/  ht40_max_power_offset; int /*<<< orphan*/  ofdm_tx_power_index_diff; int /*<<< orphan*/  ht20_tx_power_index_diff; int /*<<< orphan*/  ht40_1s_tx_power_index_B; int /*<<< orphan*/  ht40_1s_tx_power_index_A; int /*<<< orphan*/  cck_tx_power_index_B; int /*<<< orphan*/  cck_tx_power_index_A; int /*<<< orphan*/  mac_addr; } ;
struct TYPE_3__ {struct rtl8723au_efuse efuse8723; } ;
struct rtl8xxxu_priv {int has_xtalk; int xtalk; TYPE_2__* udev; int /*<<< orphan*/ * power_base; TYPE_1__ efuse_wifi; int /*<<< orphan*/  ht20_max_power_offset; int /*<<< orphan*/  ht40_max_power_offset; int /*<<< orphan*/  ofdm_tx_power_index_diff; int /*<<< orphan*/  ht20_tx_power_index_diff; int /*<<< orphan*/  ht40_1s_tx_power_index_B; int /*<<< orphan*/  ht40_1s_tx_power_index_A; int /*<<< orphan*/  cck_tx_power_index_B; int /*<<< orphan*/  cck_tx_power_index_A; int /*<<< orphan*/  mac_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8723a_power_base ; 

__attribute__((used)) static int rtl8723au_parse_efuse(struct rtl8xxxu_priv *priv)
{
	struct rtl8723au_efuse *efuse = &priv->efuse_wifi.efuse8723;

	if (efuse->rtl_id != cpu_to_le16(0x8129))
		return -EINVAL;

	ether_addr_copy(priv->mac_addr, efuse->mac_addr);

	memcpy(priv->cck_tx_power_index_A,
	       efuse->cck_tx_power_index_A,
	       sizeof(efuse->cck_tx_power_index_A));
	memcpy(priv->cck_tx_power_index_B,
	       efuse->cck_tx_power_index_B,
	       sizeof(efuse->cck_tx_power_index_B));

	memcpy(priv->ht40_1s_tx_power_index_A,
	       efuse->ht40_1s_tx_power_index_A,
	       sizeof(efuse->ht40_1s_tx_power_index_A));
	memcpy(priv->ht40_1s_tx_power_index_B,
	       efuse->ht40_1s_tx_power_index_B,
	       sizeof(efuse->ht40_1s_tx_power_index_B));

	memcpy(priv->ht20_tx_power_index_diff,
	       efuse->ht20_tx_power_index_diff,
	       sizeof(efuse->ht20_tx_power_index_diff));
	memcpy(priv->ofdm_tx_power_index_diff,
	       efuse->ofdm_tx_power_index_diff,
	       sizeof(efuse->ofdm_tx_power_index_diff));

	memcpy(priv->ht40_max_power_offset,
	       efuse->ht40_max_power_offset,
	       sizeof(efuse->ht40_max_power_offset));
	memcpy(priv->ht20_max_power_offset,
	       efuse->ht20_max_power_offset,
	       sizeof(efuse->ht20_max_power_offset));

	if (priv->efuse_wifi.efuse8723.version >= 0x01) {
		priv->has_xtalk = 1;
		priv->xtalk = priv->efuse_wifi.efuse8723.xtal_k & 0x3f;
	}

	priv->power_base = &rtl8723a_power_base;

	dev_info(&priv->udev->dev, "Vendor: %.7s\n",
		 efuse->vendor_name);
	dev_info(&priv->udev->dev, "Product: %.41s\n",
		 efuse->device_name);
	return 0;
}