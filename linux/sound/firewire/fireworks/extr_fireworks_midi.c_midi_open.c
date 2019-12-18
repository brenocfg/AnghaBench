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
struct snd_efw {int /*<<< orphan*/  mutex; int /*<<< orphan*/  substreams_counter; } ;
struct TYPE_2__ {struct snd_efw* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_efw_stream_lock_release (struct snd_efw*) ; 
 int snd_efw_stream_lock_try (struct snd_efw*) ; 
 int snd_efw_stream_reserve_duplex (struct snd_efw*,int /*<<< orphan*/ ) ; 
 int snd_efw_stream_start_duplex (struct snd_efw*) ; 

__attribute__((used)) static int midi_open(struct snd_rawmidi_substream *substream)
{
	struct snd_efw *efw = substream->rmidi->private_data;
	int err;

	err = snd_efw_stream_lock_try(efw);
	if (err < 0)
		goto end;

	mutex_lock(&efw->mutex);
	err = snd_efw_stream_reserve_duplex(efw, 0);
	if (err >= 0) {
		++efw->substreams_counter;
		err = snd_efw_stream_start_duplex(efw);
		if (err < 0)
			--efw->substreams_counter;
	}
	mutex_unlock(&efw->mutex);
	if (err < 0)
		snd_efw_stream_lock_release(efw);
end:
	return err;
}