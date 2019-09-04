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
typedef  enum da7219_aad_jack_rem_deb { ____Placeholder_da7219_aad_jack_rem_deb } da7219_aad_jack_rem_deb ;

/* Variables and functions */
 int DA7219_AAD_JACK_REM_DEB_10MS ; 
 int DA7219_AAD_JACK_REM_DEB_1MS ; 
 int DA7219_AAD_JACK_REM_DEB_20MS ; 
 int DA7219_AAD_JACK_REM_DEB_5MS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum da7219_aad_jack_rem_deb
	da7219_aad_fw_jack_rem_deb(struct snd_soc_component *component, u32 val)
{
	switch (val) {
	case 1:
		return DA7219_AAD_JACK_REM_DEB_1MS;
	case 5:
		return DA7219_AAD_JACK_REM_DEB_5MS;
	case 10:
		return DA7219_AAD_JACK_REM_DEB_10MS;
	case 20:
		return DA7219_AAD_JACK_REM_DEB_20MS;
	default:
		dev_warn(component->dev, "Invalid jack removal debounce");
		return DA7219_AAD_JACK_REM_DEB_1MS;
	}
}