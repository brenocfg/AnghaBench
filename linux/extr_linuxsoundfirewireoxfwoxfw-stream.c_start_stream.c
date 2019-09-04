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
typedef  int /*<<< orphan*/  u8 ;
struct snd_oxfw_stream_formation {unsigned int rate; unsigned int pcm; int midi; } ;
struct TYPE_2__ {int /*<<< orphan*/  channel; } ;
struct cmp_connection {int /*<<< orphan*/  speed; TYPE_1__ resources; } ;
struct amdtp_stream {int dummy; } ;
struct snd_oxfw {struct cmp_connection out_conn; int /*<<< orphan*/ ** tx_stream_formats; struct cmp_connection in_conn; int /*<<< orphan*/ ** rx_stream_formats; struct amdtp_stream rx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK_TIMEOUT ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 unsigned int SND_OXFW_STREAM_FORMAT_ENTRIES ; 
 int amdtp_am824_set_parameters (struct amdtp_stream*,unsigned int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  amdtp_stream_get_max_payload (struct amdtp_stream*) ; 
 int amdtp_stream_start (struct amdtp_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdtp_stream_wait_callback (struct amdtp_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_connection_break (struct cmp_connection*) ; 
 int cmp_connection_establish (struct cmp_connection*,int /*<<< orphan*/ ) ; 
 int snd_oxfw_stream_parse_format (int /*<<< orphan*/ *,struct snd_oxfw_stream_formation*) ; 
 int /*<<< orphan*/  stop_stream (struct snd_oxfw*,struct amdtp_stream*) ; 

__attribute__((used)) static int start_stream(struct snd_oxfw *oxfw, struct amdtp_stream *stream,
			unsigned int rate, unsigned int pcm_channels)
{
	u8 **formats;
	struct cmp_connection *conn;
	struct snd_oxfw_stream_formation formation;
	unsigned int i, midi_ports;
	int err;

	if (stream == &oxfw->rx_stream) {
		formats = oxfw->rx_stream_formats;
		conn = &oxfw->in_conn;
	} else {
		formats = oxfw->tx_stream_formats;
		conn = &oxfw->out_conn;
	}

	/* Get stream format */
	for (i = 0; i < SND_OXFW_STREAM_FORMAT_ENTRIES; i++) {
		if (formats[i] == NULL)
			break;

		err = snd_oxfw_stream_parse_format(formats[i], &formation);
		if (err < 0)
			goto end;
		if (rate != formation.rate)
			continue;
		if (pcm_channels == 0 ||  pcm_channels == formation.pcm)
			break;
	}
	if (i == SND_OXFW_STREAM_FORMAT_ENTRIES) {
		err = -EINVAL;
		goto end;
	}

	pcm_channels = formation.pcm;
	midi_ports = formation.midi * 8;

	/* The stream should have one pcm channels at least */
	if (pcm_channels == 0) {
		err = -EINVAL;
		goto end;
	}
	err = amdtp_am824_set_parameters(stream, rate, pcm_channels, midi_ports,
					 false);
	if (err < 0)
		goto end;

	err = cmp_connection_establish(conn,
				       amdtp_stream_get_max_payload(stream));
	if (err < 0)
		goto end;

	err = amdtp_stream_start(stream,
				 conn->resources.channel,
				 conn->speed);
	if (err < 0) {
		cmp_connection_break(conn);
		goto end;
	}

	/* Wait first packet */
	if (!amdtp_stream_wait_callback(stream, CALLBACK_TIMEOUT)) {
		stop_stream(oxfw, stream);
		err = -ETIMEDOUT;
	}
end:
	return err;
}