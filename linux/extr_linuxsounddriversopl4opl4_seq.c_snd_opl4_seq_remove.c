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
struct snd_seq_device {int dummy; } ;
struct snd_opl4 {int seq_client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SNDRV_SEQ_DEVICE_ARGPTR (struct snd_seq_device*) ; 
 int /*<<< orphan*/  snd_seq_delete_kernel_client (int) ; 
 struct snd_seq_device* to_seq_dev (struct device*) ; 

__attribute__((used)) static int snd_opl4_seq_remove(struct device *_dev)
{
	struct snd_seq_device *dev = to_seq_dev(_dev);
	struct snd_opl4 *opl4;

	opl4 = *(struct snd_opl4 **)SNDRV_SEQ_DEVICE_ARGPTR(dev);
	if (!opl4)
		return -EINVAL;

	if (opl4->seq_client >= 0) {
		snd_seq_delete_kernel_client(opl4->seq_client);
		opl4->seq_client = -1;
	}
	return 0;
}