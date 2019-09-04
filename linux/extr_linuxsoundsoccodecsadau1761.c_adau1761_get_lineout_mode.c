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
struct snd_soc_component {TYPE_1__* dev; } ;
struct adau1761_platform_data {int lineout_mode; } ;
typedef  enum adau1761_output_mode { ____Placeholder_adau1761_output_mode } adau1761_output_mode ;
struct TYPE_2__ {struct adau1761_platform_data* platform_data; } ;

/* Variables and functions */
 int ADAU1761_OUTPUT_MODE_LINE ; 

__attribute__((used)) static enum adau1761_output_mode adau1761_get_lineout_mode(
	struct snd_soc_component *component)
{
	struct adau1761_platform_data *pdata = component->dev->platform_data;

	if (pdata)
		return pdata->lineout_mode;

	return ADAU1761_OUTPUT_MODE_LINE;
}