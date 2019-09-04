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
struct snd_rawmidi_substream {TYPE_1__* ops; int /*<<< orphan*/  rmidi; struct snd_rawmidi_runtime* runtime; } ;
struct snd_rawmidi_runtime {int drain; scalar_t__ avail; scalar_t__ buffer_size; int /*<<< orphan*/  sleep; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* drain ) (struct snd_rawmidi_substream*) ;} ;

/* Variables and functions */
 int EIO ; 
 int ERESTARTSYS ; 
 int HZ ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rmidi_warn (int /*<<< orphan*/ ,char*,long,long) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rawmidi_drop_output (struct snd_rawmidi_substream*) ; 
 int /*<<< orphan*/  stub1 (struct snd_rawmidi_substream*) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

int snd_rawmidi_drain_output(struct snd_rawmidi_substream *substream)
{
	int err;
	long timeout;
	struct snd_rawmidi_runtime *runtime = substream->runtime;

	err = 0;
	runtime->drain = 1;
	timeout = wait_event_interruptible_timeout(runtime->sleep,
				(runtime->avail >= runtime->buffer_size),
				10*HZ);
	if (signal_pending(current))
		err = -ERESTARTSYS;
	if (runtime->avail < runtime->buffer_size && !timeout) {
		rmidi_warn(substream->rmidi,
			   "rawmidi drain error (avail = %li, buffer_size = %li)\n",
			   (long)runtime->avail, (long)runtime->buffer_size);
		err = -EIO;
	}
	runtime->drain = 0;
	if (err != -ERESTARTSYS) {
		/* we need wait a while to make sure that Tx FIFOs are empty */
		if (substream->ops->drain)
			substream->ops->drain(substream);
		else
			msleep(50);
		snd_rawmidi_drop_output(substream);
	}
	return err;
}