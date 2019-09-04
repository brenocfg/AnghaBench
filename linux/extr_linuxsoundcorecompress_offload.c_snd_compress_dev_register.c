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
struct snd_device {struct snd_compr* device_data; } ;
struct snd_compr {int /*<<< orphan*/  dev; int /*<<< orphan*/  device; int /*<<< orphan*/  card; int /*<<< orphan*/  direction; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EBADFD ; 
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_DEVICE_TYPE_COMPRESS ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_compr_file_ops ; 
 int snd_register_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct snd_compr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_compress_dev_register(struct snd_device *device)
{
	int ret = -EINVAL;
	struct snd_compr *compr;

	if (snd_BUG_ON(!device || !device->device_data))
		return -EBADFD;
	compr = device->device_data;

	pr_debug("reg device %s, direction %d\n", compr->name,
			compr->direction);
	/* register compressed device */
	ret = snd_register_device(SNDRV_DEVICE_TYPE_COMPRESS,
				  compr->card, compr->device,
				  &snd_compr_file_ops, compr, &compr->dev);
	if (ret < 0) {
		pr_err("snd_register_device failed %d\n", ret);
		return ret;
	}
	return ret;

}