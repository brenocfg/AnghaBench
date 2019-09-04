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
struct snd_virmidi_dev {scalar_t__ seq_mode; } ;
struct snd_rawmidi {struct snd_virmidi_dev* private_data; } ;

/* Variables and functions */
 scalar_t__ SNDRV_VIRMIDI_SEQ_DISPATCH ; 
 int /*<<< orphan*/  snd_virmidi_dev_detach_seq (struct snd_virmidi_dev*) ; 

__attribute__((used)) static int snd_virmidi_dev_unregister(struct snd_rawmidi *rmidi)
{
	struct snd_virmidi_dev *rdev = rmidi->private_data;

	if (rdev->seq_mode == SNDRV_VIRMIDI_SEQ_DISPATCH)
		snd_virmidi_dev_detach_seq(rdev);
	return 0;
}