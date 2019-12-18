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
struct snd_bebob {int /*<<< orphan*/  mutex; int /*<<< orphan*/  substreams_counter; } ;
struct TYPE_2__ {struct snd_bebob* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_bebob_stream_lock_release (struct snd_bebob*) ; 
 int /*<<< orphan*/  snd_bebob_stream_stop_duplex (struct snd_bebob*) ; 

__attribute__((used)) static int midi_close(struct snd_rawmidi_substream *substream)
{
	struct snd_bebob *bebob = substream->rmidi->private_data;

	mutex_lock(&bebob->mutex);
	bebob->substreams_counter--;
	snd_bebob_stream_stop_duplex(bebob);
	mutex_unlock(&bebob->mutex);

	snd_bebob_stream_lock_release(bebob);
	return 0;
}