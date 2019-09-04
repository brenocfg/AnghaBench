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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum da7219_aad_jack_det_rate { ____Placeholder_da7219_aad_jack_det_rate } da7219_aad_jack_det_rate ;

/* Variables and functions */
 int DA7219_AAD_JACK_DET_RATE_128_256MS ; 
 int DA7219_AAD_JACK_DET_RATE_256_512MS ; 
 int DA7219_AAD_JACK_DET_RATE_32_64MS ; 
 int DA7219_AAD_JACK_DET_RATE_64_128MS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static enum da7219_aad_jack_det_rate
	da7219_aad_fw_jack_det_rate(struct snd_soc_component *component, const char *str)
{
	if (!strcmp(str, "32ms_64ms")) {
		return DA7219_AAD_JACK_DET_RATE_32_64MS;
	} else if (!strcmp(str, "64ms_128ms")) {
		return DA7219_AAD_JACK_DET_RATE_64_128MS;
	} else if (!strcmp(str, "128ms_256ms")) {
		return DA7219_AAD_JACK_DET_RATE_128_256MS;
	} else if (!strcmp(str, "256ms_512ms")) {
		return DA7219_AAD_JACK_DET_RATE_256_512MS;
	} else {
		dev_warn(component->dev, "Invalid jack detect rate");
		return DA7219_AAD_JACK_DET_RATE_256_512MS;
	}
}