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
struct snd_soc_acpi_mach {int /*<<< orphan*/ * quirk_data; } ;
struct snd_soc_acpi_codecs {int num_codecs; int /*<<< orphan*/ * codecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_dev_present (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

struct snd_soc_acpi_mach *snd_soc_acpi_codec_list(void *arg)
{
	struct snd_soc_acpi_mach *mach = arg;
	struct snd_soc_acpi_codecs *codec_list =
		(struct snd_soc_acpi_codecs *) mach->quirk_data;
	int i;

	if (mach->quirk_data == NULL)
		return mach;

	for (i = 0; i < codec_list->num_codecs; i++) {
		if (!acpi_dev_present(codec_list->codecs[i], NULL, -1))
			return NULL;
	}

	return mach;
}