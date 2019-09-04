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
struct rtl8xxxu_priv {int chip_cut; int /*<<< orphan*/  enable_bluetooth; } ;

/* Variables and functions */
 int EINVAL ; 
 int rtl8xxxu_load_firmware (struct rtl8xxxu_priv*,char*) ; 

__attribute__((used)) static int rtl8723au_load_firmware(struct rtl8xxxu_priv *priv)
{
	char *fw_name;
	int ret;

	switch (priv->chip_cut) {
	case 0:
		fw_name = "rtlwifi/rtl8723aufw_A.bin";
		break;
	case 1:
		if (priv->enable_bluetooth)
			fw_name = "rtlwifi/rtl8723aufw_B.bin";
		else
			fw_name = "rtlwifi/rtl8723aufw_B_NoBT.bin";

		break;
	default:
		return -EINVAL;
	}

	ret = rtl8xxxu_load_firmware(priv, fw_name);
	return ret;
}