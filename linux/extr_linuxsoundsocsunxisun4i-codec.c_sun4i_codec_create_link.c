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
struct snd_soc_dai_link {char* name; char* stream_name; char* codec_dai_name; int /*<<< orphan*/  dai_fmt; void* platform_name; void* codec_name; void* cpu_dai_name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SND_SOC_DAIFMT_I2S ; 
 void* dev_name (struct device*) ; 
 struct snd_soc_dai_link* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct snd_soc_dai_link *sun4i_codec_create_link(struct device *dev,
							int *num_links)
{
	struct snd_soc_dai_link *link = devm_kzalloc(dev, sizeof(*link),
						     GFP_KERNEL);
	if (!link)
		return NULL;

	link->name		= "cdc";
	link->stream_name	= "CDC PCM";
	link->codec_dai_name	= "Codec";
	link->cpu_dai_name	= dev_name(dev);
	link->codec_name	= dev_name(dev);
	link->platform_name	= dev_name(dev);
	link->dai_fmt		= SND_SOC_DAIFMT_I2S;

	*num_links = 1;

	return link;
}