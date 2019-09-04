#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {int num_codecs; TYPE_2__* card; TYPE_1__** codec_dais; } ;
struct snd_soc_component {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  dapm_mutex; } ;
struct TYPE_3__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 scalar_t__ dapm_widget_show_component (struct snd_soc_component*,char*) ; 
 struct snd_soc_pcm_runtime* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t dapm_widget_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct snd_soc_pcm_runtime *rtd = dev_get_drvdata(dev);
	int i, count = 0;

	mutex_lock(&rtd->card->dapm_mutex);

	for (i = 0; i < rtd->num_codecs; i++) {
		struct snd_soc_component *cmpnt = rtd->codec_dais[i]->component;

		count += dapm_widget_show_component(cmpnt, buf + count);
	}

	mutex_unlock(&rtd->card->dapm_mutex);

	return count;
}