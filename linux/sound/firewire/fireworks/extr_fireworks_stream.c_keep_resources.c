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
struct cmp_connection {int dummy; } ;
struct amdtp_stream {int dummy; } ;
struct snd_efw {unsigned int* pcm_capture_channels; unsigned int midi_out_ports; unsigned int* pcm_playback_channels; unsigned int midi_in_ports; struct cmp_connection in_conn; struct cmp_connection out_conn; struct amdtp_stream tx_stream; } ;

/* Variables and functions */
 int amdtp_am824_set_parameters (struct amdtp_stream*,unsigned int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  amdtp_stream_get_max_payload (struct amdtp_stream*) ; 
 int cmp_connection_reserve (struct cmp_connection*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int keep_resources(struct snd_efw *efw, struct amdtp_stream *stream,
			  unsigned int rate, unsigned int mode)
{
	unsigned int pcm_channels;
	unsigned int midi_ports;
	struct cmp_connection *conn;
	int err;

	if (stream == &efw->tx_stream) {
		pcm_channels = efw->pcm_capture_channels[mode];
		midi_ports = efw->midi_out_ports;
		conn = &efw->out_conn;
	} else {
		pcm_channels = efw->pcm_playback_channels[mode];
		midi_ports = efw->midi_in_ports;
		conn = &efw->in_conn;
	}

	err = amdtp_am824_set_parameters(stream, rate, pcm_channels,
					 midi_ports, false);
	if (err < 0)
		return err;

	return cmp_connection_reserve(conn, amdtp_stream_get_max_payload(stream));
}