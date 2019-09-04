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
typedef  enum da7219_aad_btn_avg { ____Placeholder_da7219_aad_btn_avg } da7219_aad_btn_avg ;

/* Variables and functions */
 int DA7219_AAD_BTN_AVG_1 ; 
 int DA7219_AAD_BTN_AVG_2 ; 
 int DA7219_AAD_BTN_AVG_4 ; 
 int DA7219_AAD_BTN_AVG_8 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum da7219_aad_btn_avg
	da7219_aad_fw_btn_avg(struct snd_soc_component *component, u32 val)
{
	switch (val) {
	case 1:
		return DA7219_AAD_BTN_AVG_1;
	case 2:
		return DA7219_AAD_BTN_AVG_2;
	case 4:
		return DA7219_AAD_BTN_AVG_4;
	case 8:
		return DA7219_AAD_BTN_AVG_8;
	default:
		dev_warn(component->dev, "Invalid button average value");
		return DA7219_AAD_BTN_AVG_2;
	}
}