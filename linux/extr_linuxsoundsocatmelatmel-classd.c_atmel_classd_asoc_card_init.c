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
struct snd_soc_dai_link {char* name; char* stream_name; void* platform_name; void* codec_name; void* cpu_dai_name; int /*<<< orphan*/  codec_dai_name; } ;
struct snd_soc_card {int num_links; struct device* dev; int /*<<< orphan*/  name; struct snd_soc_dai_link* dai_link; } ;
struct device {int dummy; } ;
struct atmel_classd {TYPE_1__* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  card_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_CLASSD_CODEC_DAI_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dev_name (struct device*) ; 
 struct snd_soc_dai_link* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct atmel_classd* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static int atmel_classd_asoc_card_init(struct device *dev,
					struct snd_soc_card *card)
{
	struct snd_soc_dai_link *dai_link;
	struct atmel_classd *dd = snd_soc_card_get_drvdata(card);

	dai_link = devm_kzalloc(dev, sizeof(*dai_link), GFP_KERNEL);
	if (!dai_link)
		return -ENOMEM;

	dai_link->name			= "CLASSD";
	dai_link->stream_name		= "CLASSD PCM";
	dai_link->codec_dai_name	= ATMEL_CLASSD_CODEC_DAI_NAME;
	dai_link->cpu_dai_name		= dev_name(dev);
	dai_link->codec_name		= dev_name(dev);
	dai_link->platform_name		= dev_name(dev);

	card->dai_link	= dai_link;
	card->num_links	= 1;
	card->name	= dd->pdata->card_name;
	card->dev	= dev;

	return 0;
}