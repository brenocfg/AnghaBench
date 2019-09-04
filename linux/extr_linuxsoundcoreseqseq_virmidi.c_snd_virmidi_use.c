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
struct snd_virmidi_dev {int /*<<< orphan*/  flags; TYPE_1__* card; } ;
struct snd_seq_port_subscribe {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  SNDRV_VIRMIDI_USE ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_virmidi_use(void *private_data,
			   struct snd_seq_port_subscribe *info)
{
	struct snd_virmidi_dev *rdev;

	rdev = private_data;
	if (!try_module_get(rdev->card->module))
		return -EFAULT;
	rdev->flags |= SNDRV_VIRMIDI_USE;
	return 0;
}