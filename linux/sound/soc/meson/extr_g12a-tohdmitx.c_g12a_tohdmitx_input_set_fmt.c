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
struct snd_soc_dai {struct g12a_tohdmitx_input* playback_dma_data; } ;
struct g12a_tohdmitx_input {unsigned int fmt; } ;

/* Variables and functions */

__attribute__((used)) static int g12a_tohdmitx_input_set_fmt(struct snd_soc_dai *dai,
				       unsigned int fmt)
{
	struct g12a_tohdmitx_input *data = dai->playback_dma_data;

	/* Save the source stream format for the downstream link */
	data->fmt = fmt;
	return 0;
}