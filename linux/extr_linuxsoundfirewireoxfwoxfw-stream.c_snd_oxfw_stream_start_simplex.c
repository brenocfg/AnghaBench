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
struct snd_oxfw_stream_formation {unsigned int rate; unsigned int pcm; } ;
struct amdtp_stream {int dummy; } ;
struct snd_oxfw {unsigned int capture_substreams; unsigned int playback_substreams; TYPE_1__* unit; struct amdtp_stream rx_stream; scalar_t__ has_output; struct amdtp_stream tx_stream; } ;
typedef  enum avc_general_plug_dir { ____Placeholder_avc_general_plug_dir } avc_general_plug_dir ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int AVC_GENERAL_PLUG_DIR_IN ; 
 int AVC_GENERAL_PLUG_DIR_OUT ; 
 int /*<<< orphan*/  amdtp_stream_running (struct amdtp_stream*) ; 
 scalar_t__ amdtp_streaming_error (struct amdtp_stream*) ; 
 int check_connection_used_by_others (struct snd_oxfw*,struct amdtp_stream*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int set_stream_format (struct snd_oxfw*,struct amdtp_stream*,unsigned int,unsigned int) ; 
 int snd_oxfw_stream_get_current_formation (struct snd_oxfw*,int,struct snd_oxfw_stream_formation*) ; 
 int start_stream (struct snd_oxfw*,struct amdtp_stream*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stop_stream (struct snd_oxfw*,struct amdtp_stream*) ; 

int snd_oxfw_stream_start_simplex(struct snd_oxfw *oxfw,
				  struct amdtp_stream *stream,
				  unsigned int rate, unsigned int pcm_channels)
{
	struct amdtp_stream *opposite;
	struct snd_oxfw_stream_formation formation;
	enum avc_general_plug_dir dir;
	unsigned int substreams, opposite_substreams;
	int err = 0;

	if (stream == &oxfw->tx_stream) {
		substreams = oxfw->capture_substreams;
		opposite = &oxfw->rx_stream;
		opposite_substreams = oxfw->playback_substreams;
		dir = AVC_GENERAL_PLUG_DIR_OUT;
	} else {
		substreams = oxfw->playback_substreams;
		opposite_substreams = oxfw->capture_substreams;

		if (oxfw->has_output)
			opposite = &oxfw->rx_stream;
		else
			opposite = NULL;

		dir = AVC_GENERAL_PLUG_DIR_IN;
	}

	if (substreams == 0)
		goto end;

	/*
	 * Considering JACK/FFADO streaming:
	 * TODO: This can be removed hwdep functionality becomes popular.
	 */
	err = check_connection_used_by_others(oxfw, stream);
	if (err < 0)
		goto end;

	/* packet queueing error */
	if (amdtp_streaming_error(stream))
		stop_stream(oxfw, stream);

	err = snd_oxfw_stream_get_current_formation(oxfw, dir, &formation);
	if (err < 0)
		goto end;
	if (rate == 0)
		rate = formation.rate;
	if (pcm_channels == 0)
		pcm_channels = formation.pcm;

	if ((formation.rate != rate) || (formation.pcm != pcm_channels)) {
		if (opposite != NULL) {
			err = check_connection_used_by_others(oxfw, opposite);
			if (err < 0)
				goto end;
			stop_stream(oxfw, opposite);
		}
		stop_stream(oxfw, stream);

		err = set_stream_format(oxfw, stream, rate, pcm_channels);
		if (err < 0) {
			dev_err(&oxfw->unit->device,
				"fail to set stream format: %d\n", err);
			goto end;
		}

		/* Start opposite stream if needed. */
		if (opposite && !amdtp_stream_running(opposite) &&
		    (opposite_substreams > 0)) {
			err = start_stream(oxfw, opposite, rate, 0);
			if (err < 0) {
				dev_err(&oxfw->unit->device,
					"fail to restart stream: %d\n", err);
				goto end;
			}
		}
	}

	/* Start requested stream. */
	if (!amdtp_stream_running(stream)) {
		err = start_stream(oxfw, stream, rate, pcm_channels);
		if (err < 0)
			dev_err(&oxfw->unit->device,
				"fail to start stream: %d\n", err);
	}
end:
	return err;
}