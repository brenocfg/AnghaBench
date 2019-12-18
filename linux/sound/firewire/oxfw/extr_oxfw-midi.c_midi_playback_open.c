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
struct snd_oxfw {int /*<<< orphan*/  mutex; int /*<<< orphan*/  substreams_count; int /*<<< orphan*/  rx_stream; } ;
struct TYPE_2__ {struct snd_oxfw* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_oxfw_stream_lock_release (struct snd_oxfw*) ; 
 int snd_oxfw_stream_lock_try (struct snd_oxfw*) ; 
 int snd_oxfw_stream_reserve_duplex (struct snd_oxfw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_oxfw_stream_start_duplex (struct snd_oxfw*) ; 

__attribute__((used)) static int midi_playback_open(struct snd_rawmidi_substream *substream)
{
	struct snd_oxfw *oxfw = substream->rmidi->private_data;
	int err;

	err = snd_oxfw_stream_lock_try(oxfw);
	if (err < 0)
		return err;

	mutex_lock(&oxfw->mutex);

	err = snd_oxfw_stream_reserve_duplex(oxfw, &oxfw->rx_stream, 0, 0);
	if (err >= 0) {
		++oxfw->substreams_count;
		err = snd_oxfw_stream_start_duplex(oxfw);
	}

	mutex_unlock(&oxfw->mutex);

	if (err < 0)
		snd_oxfw_stream_lock_release(oxfw);

	return err;
}