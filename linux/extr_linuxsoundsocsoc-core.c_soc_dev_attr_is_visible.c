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
typedef  int /*<<< orphan*/  umode_t ;
struct snd_soc_pcm_runtime {scalar_t__ num_codecs; } ;
struct kobject {int dummy; } ;
struct device {int dummy; } ;
struct attribute {int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {struct attribute attr; } ;

/* Variables and functions */
 TYPE_1__ dev_attr_pmdown_time ; 
 struct snd_soc_pcm_runtime* dev_get_drvdata (struct device*) ; 
 struct device* kobj_to_dev (struct kobject*) ; 

__attribute__((used)) static umode_t soc_dev_attr_is_visible(struct kobject *kobj,
				       struct attribute *attr, int idx)
{
	struct device *dev = kobj_to_dev(kobj);
	struct snd_soc_pcm_runtime *rtd = dev_get_drvdata(dev);

	if (attr == &dev_attr_pmdown_time.attr)
		return attr->mode; /* always visible */
	return rtd->num_codecs ? attr->mode : 0; /* enabled only with codec */
}