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
struct snd_compr {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_compress_dev_disconnect(struct snd_device *device)
{
	struct snd_compr *compr;

	compr = device->device_data;
	snd_unregister_device(&compr->dev);
	return 0;
}