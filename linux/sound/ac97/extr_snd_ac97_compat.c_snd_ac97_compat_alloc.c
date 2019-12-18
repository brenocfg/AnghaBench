#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct snd_ac97 {TYPE_1__ dev; int /*<<< orphan*/ * bus; struct ac97_codec_device* private_data; } ;
struct ac97_codec_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct snd_ac97* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  compat_ac97_release ; 
 int /*<<< orphan*/  compat_soc_ac97_bus ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int device_register (TYPE_1__*) ; 
 struct snd_ac97* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 

struct snd_ac97 *snd_ac97_compat_alloc(struct ac97_codec_device *adev)
{
	struct snd_ac97 *ac97;
	int ret;

	ac97 = kzalloc(sizeof(struct snd_ac97), GFP_KERNEL);
	if (ac97 == NULL)
		return ERR_PTR(-ENOMEM);

	ac97->private_data = adev;
	ac97->bus = &compat_soc_ac97_bus;

	ac97->dev.parent = &adev->dev;
	ac97->dev.release = compat_ac97_release;
	dev_set_name(&ac97->dev, "%s-compat", dev_name(&adev->dev));
	ret = device_register(&ac97->dev);
	if (ret) {
		put_device(&ac97->dev);
		return ERR_PTR(ret);
	}

	return ac97;
}