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
typedef  enum da7218_dmic_data_sel { ____Placeholder_da7218_dmic_data_sel } da7218_dmic_data_sel ;

/* Variables and functions */
 int DA7218_DMIC_DATA_LFALL_RRISE ; 
 int DA7218_DMIC_DATA_LRISE_RFALL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static enum da7218_dmic_data_sel
	da7218_of_dmic_data_sel(struct snd_soc_component *component, const char *str)
{
	if (!strcmp(str, "lrise_rfall")) {
		return DA7218_DMIC_DATA_LRISE_RFALL;
	} else if (!strcmp(str, "lfall_rrise")) {
		return DA7218_DMIC_DATA_LFALL_RRISE;
	} else {
		dev_warn(component->dev, "Invalid DMIC data type selection");
		return DA7218_DMIC_DATA_LRISE_RFALL;
	}
}