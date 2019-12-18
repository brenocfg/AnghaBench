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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum da7219_aad_btn_cfg { ____Placeholder_da7219_aad_btn_cfg } da7219_aad_btn_cfg ;

/* Variables and functions */
 int DA7219_AAD_BTN_CFG_100MS ; 
 int DA7219_AAD_BTN_CFG_10MS ; 
 int DA7219_AAD_BTN_CFG_200MS ; 
 int DA7219_AAD_BTN_CFG_2MS ; 
 int DA7219_AAD_BTN_CFG_500MS ; 
 int DA7219_AAD_BTN_CFG_50MS ; 
 int DA7219_AAD_BTN_CFG_5MS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum da7219_aad_btn_cfg
	da7219_aad_fw_btn_cfg(struct snd_soc_component *component, u32 val)
{
	switch (val) {
	case 2:
		return DA7219_AAD_BTN_CFG_2MS;
	case 5:
		return DA7219_AAD_BTN_CFG_5MS;
	case 10:
		return DA7219_AAD_BTN_CFG_10MS;
	case 50:
		return DA7219_AAD_BTN_CFG_50MS;
	case 100:
		return DA7219_AAD_BTN_CFG_100MS;
	case 200:
		return DA7219_AAD_BTN_CFG_200MS;
	case 500:
		return DA7219_AAD_BTN_CFG_500MS;
	default:
		dev_warn(component->dev, "Invalid button config");
		return DA7219_AAD_BTN_CFG_10MS;
	}
}