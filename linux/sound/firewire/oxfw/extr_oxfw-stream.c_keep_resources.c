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
typedef  int /*<<< orphan*/  u8 ;
struct snd_oxfw_stream_formation {scalar_t__ rate; scalar_t__ pcm; scalar_t__ midi; } ;
struct cmp_connection {int dummy; } ;
struct amdtp_stream {int dummy; } ;
struct snd_oxfw {struct cmp_connection out_conn; int /*<<< orphan*/ ** tx_stream_formats; struct cmp_connection in_conn; int /*<<< orphan*/ ** rx_stream_formats; struct amdtp_stream rx_stream; } ;
typedef  enum avc_general_plug_dir { ____Placeholder_avc_general_plug_dir } avc_general_plug_dir ;

/* Variables and functions */
 int AVC_GENERAL_PLUG_DIR_IN ; 
 int AVC_GENERAL_PLUG_DIR_OUT ; 
 int EINVAL ; 
 int SND_OXFW_STREAM_FORMAT_ENTRIES ; 
 int amdtp_am824_set_parameters (struct amdtp_stream*,scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  amdtp_stream_get_max_payload (struct amdtp_stream*) ; 
 int cmp_connection_reserve (struct cmp_connection*,int /*<<< orphan*/ ) ; 
 int snd_oxfw_stream_get_current_formation (struct snd_oxfw*,int,struct snd_oxfw_stream_formation*) ; 
 int snd_oxfw_stream_parse_format (int /*<<< orphan*/ *,struct snd_oxfw_stream_formation*) ; 

__attribute__((used)) static int keep_resources(struct snd_oxfw *oxfw, struct amdtp_stream *stream)
{
	enum avc_general_plug_dir dir;
	u8 **formats;
	struct snd_oxfw_stream_formation formation;
	struct cmp_connection *conn;
	int i;
	int err;

	if (stream == &oxfw->rx_stream) {
		dir = AVC_GENERAL_PLUG_DIR_IN;
		formats = oxfw->rx_stream_formats;
		conn = &oxfw->in_conn;
	} else {
		dir = AVC_GENERAL_PLUG_DIR_OUT;
		formats = oxfw->tx_stream_formats;
		conn = &oxfw->out_conn;
	}

	err = snd_oxfw_stream_get_current_formation(oxfw, dir, &formation);
	if (err < 0)
		return err;

	for (i = 0; i < SND_OXFW_STREAM_FORMAT_ENTRIES; i++) {
		struct snd_oxfw_stream_formation fmt;

		if (formats[i] == NULL)
			break;

		err = snd_oxfw_stream_parse_format(formats[i], &fmt);
		if (err < 0)
			return err;

		if (fmt.rate == formation.rate && fmt.pcm == formation.pcm &&
		    fmt.midi == formation.midi)
			break;
	}
	if (i == SND_OXFW_STREAM_FORMAT_ENTRIES)
		return -EINVAL;

	// The stream should have one pcm channels at least.
	if (formation.pcm == 0)
		return -EINVAL;

	err = amdtp_am824_set_parameters(stream, formation.rate, formation.pcm,
					 formation.midi * 8, false);
	if (err < 0)
		return err;

	return cmp_connection_reserve(conn, amdtp_stream_get_max_payload(stream));
}