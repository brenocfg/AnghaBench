#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {unsigned int num_codecs; TYPE_3__** codec_dais; struct snd_soc_dai_link* dai_link; TYPE_1__* cpu_dai; } ;
struct snd_soc_dai_link {scalar_t__ symmetric_samplebits; scalar_t__ symmetric_channels; scalar_t__ symmetric_rates; } ;
struct snd_soc_dai_driver {scalar_t__ symmetric_samplebits; scalar_t__ symmetric_channels; scalar_t__ symmetric_rates; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_6__ {TYPE_2__* driver; } ;
struct TYPE_5__ {scalar_t__ symmetric_samplebits; scalar_t__ symmetric_channels; scalar_t__ symmetric_rates; } ;
struct TYPE_4__ {struct snd_soc_dai_driver* driver; } ;

/* Variables and functions */

__attribute__((used)) static bool soc_pcm_has_symmetry(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai_driver *cpu_driver = rtd->cpu_dai->driver;
	struct snd_soc_dai_link *link = rtd->dai_link;
	unsigned int symmetry, i;

	symmetry = cpu_driver->symmetric_rates || link->symmetric_rates ||
		cpu_driver->symmetric_channels || link->symmetric_channels ||
		cpu_driver->symmetric_samplebits || link->symmetric_samplebits;

	for (i = 0; i < rtd->num_codecs; i++)
		symmetry = symmetry ||
			rtd->codec_dais[i]->driver->symmetric_rates ||
			rtd->codec_dais[i]->driver->symmetric_channels ||
			rtd->codec_dais[i]->driver->symmetric_samplebits;

	return symmetry;
}