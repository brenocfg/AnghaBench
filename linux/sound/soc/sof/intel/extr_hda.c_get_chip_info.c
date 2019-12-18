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
struct sof_intel_dsp_desc {int dummy; } ;
struct sof_dev_desc {struct sof_intel_dsp_desc* chip_info; } ;
struct snd_sof_pdata {struct sof_dev_desc* desc; } ;

/* Variables and functions */

__attribute__((used)) static const struct sof_intel_dsp_desc
	*get_chip_info(struct snd_sof_pdata *pdata)
{
	const struct sof_dev_desc *desc = pdata->desc;
	const struct sof_intel_dsp_desc *chip_info;

	chip_info = desc->chip_info;

	return chip_info;
}