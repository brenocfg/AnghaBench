#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_codec {int /*<<< orphan*/  dev; } ;
struct gbaudio_codec_info {struct snd_soc_codec* codec; int /*<<< orphan*/  dai_list; int /*<<< orphan*/  lock; int /*<<< orphan*/  module_list; int /*<<< orphan*/  dev; } ;
struct gbaudio_codec_dai {int /*<<< orphan*/  list; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ ,int) ; 
 void* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* gbaudio_dai ; 
 struct gbaudio_codec_info* gbcodec ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_codec_set_drvdata (struct snd_soc_codec*,struct gbaudio_codec_info*) ; 

__attribute__((used)) static int gbcodec_probe(struct snd_soc_codec *codec)
{
	int i;
	struct gbaudio_codec_info *info;
	struct gbaudio_codec_dai *dai;

	info = devm_kzalloc(codec->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->dev = codec->dev;
	INIT_LIST_HEAD(&info->module_list);
	mutex_init(&info->lock);
	INIT_LIST_HEAD(&info->dai_list);

	/* init dai_list used to maintain runtime stream info */
	for (i = 0; i < ARRAY_SIZE(gbaudio_dai); i++) {
		dai = devm_kzalloc(codec->dev, sizeof(*dai), GFP_KERNEL);
		if (!dai)
			return -ENOMEM;
		dai->id = gbaudio_dai[i].id;
		list_add(&dai->list, &info->dai_list);
	}

	info->codec = codec;
	snd_soc_codec_set_drvdata(codec, info);
	gbcodec = info;

	device_init_wakeup(codec->dev, 1);
	return 0;
}