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
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct mts64 {scalar_t__ open_count; } ;
struct TYPE_2__ {struct mts64* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mts64_device_open (struct mts64*) ; 

__attribute__((used)) static int snd_mts64_rawmidi_open(struct snd_rawmidi_substream *substream)
{
	struct mts64 *mts = substream->rmidi->private_data;

	if (mts->open_count == 0) {
		/* We don't need a spinlock here, because this is just called 
		   if the device has not been opened before. 
		   So there aren't any IRQs from the device */
		mts64_device_open(mts);

		msleep(50);
	}
	++(mts->open_count);

	return 0;
}