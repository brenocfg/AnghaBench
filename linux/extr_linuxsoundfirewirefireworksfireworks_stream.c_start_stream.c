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
struct TYPE_2__ {int /*<<< orphan*/  channel; } ;
struct cmp_connection {int /*<<< orphan*/  speed; TYPE_1__ resources; } ;
struct amdtp_stream {int dummy; } ;
struct snd_efw {unsigned int* pcm_capture_channels; unsigned int midi_out_ports; unsigned int* pcm_playback_channels; unsigned int midi_in_ports; struct cmp_connection in_conn; struct cmp_connection out_conn; struct amdtp_stream tx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK_TIMEOUT ; 
 int ETIMEDOUT ; 
 int amdtp_am824_set_parameters (struct amdtp_stream*,unsigned int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  amdtp_stream_get_max_payload (struct amdtp_stream*) ; 
 int amdtp_stream_start (struct amdtp_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdtp_stream_wait_callback (struct amdtp_stream*,int /*<<< orphan*/ ) ; 
 int cmp_connection_establish (struct cmp_connection*,int /*<<< orphan*/ ) ; 
 int snd_efw_get_multiplier_mode (unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  stop_stream (struct snd_efw*,struct amdtp_stream*) ; 

__attribute__((used)) static int
start_stream(struct snd_efw *efw, struct amdtp_stream *stream,
	     unsigned int sampling_rate)
{
	struct cmp_connection *conn;
	unsigned int mode, pcm_channels, midi_ports;
	int err;

	err = snd_efw_get_multiplier_mode(sampling_rate, &mode);
	if (err < 0)
		goto end;
	if (stream == &efw->tx_stream) {
		conn = &efw->out_conn;
		pcm_channels = efw->pcm_capture_channels[mode];
		midi_ports = efw->midi_out_ports;
	} else {
		conn = &efw->in_conn;
		pcm_channels = efw->pcm_playback_channels[mode];
		midi_ports = efw->midi_in_ports;
	}

	err = amdtp_am824_set_parameters(stream, sampling_rate,
					 pcm_channels, midi_ports, false);
	if (err < 0)
		goto end;

	/*  establish connection via CMP */
	err = cmp_connection_establish(conn,
				amdtp_stream_get_max_payload(stream));
	if (err < 0)
		goto end;

	/* start amdtp stream */
	err = amdtp_stream_start(stream,
				 conn->resources.channel,
				 conn->speed);
	if (err < 0) {
		stop_stream(efw, stream);
		goto end;
	}

	/* wait first callback */
	if (!amdtp_stream_wait_callback(stream, CALLBACK_TIMEOUT)) {
		stop_stream(efw, stream);
		err = -ETIMEDOUT;
	}
end:
	return err;
}