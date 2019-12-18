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
struct snd_soc_dai_link_component {char* dai_name; void* name; } ;
struct snd_soc_dai_link {int num_cpus; int num_codecs; int num_platforms; char* name; char* stream_name; int /*<<< orphan*/  dai_fmt; struct snd_soc_dai_link_component* platforms; struct snd_soc_dai_link_component* codecs; struct snd_soc_dai_link_component* cpus; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SND_SOC_DAIFMT_I2S ; 
 void* dev_name (struct device*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct snd_soc_dai_link *sun4i_codec_create_link(struct device *dev,
							int *num_links)
{
	struct snd_soc_dai_link *link = devm_kzalloc(dev, sizeof(*link),
						     GFP_KERNEL);
	struct snd_soc_dai_link_component *dlc = devm_kzalloc(dev,
						3 * sizeof(*dlc), GFP_KERNEL);
	if (!link || !dlc)
		return NULL;

	link->cpus	= &dlc[0];
	link->codecs	= &dlc[1];
	link->platforms	= &dlc[2];

	link->num_cpus		= 1;
	link->num_codecs	= 1;
	link->num_platforms	= 1;

	link->name		= "cdc";
	link->stream_name	= "CDC PCM";
	link->codecs->dai_name	= "Codec";
	link->cpus->dai_name	= dev_name(dev);
	link->codecs->name	= dev_name(dev);
	link->platforms->name	= dev_name(dev);
	link->dai_fmt		= SND_SOC_DAIFMT_I2S;

	*num_links = 1;

	return link;
}