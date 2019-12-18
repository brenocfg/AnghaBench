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
struct snd_bebob_stream_formation {int /*<<< orphan*/  midi; int /*<<< orphan*/  pcm; } ;
struct cmp_connection {int dummy; } ;
struct amdtp_stream {int dummy; } ;
struct snd_bebob {struct cmp_connection in_conn; struct snd_bebob_stream_formation* rx_stream_formations; struct cmp_connection out_conn; struct snd_bebob_stream_formation* tx_stream_formations; struct amdtp_stream tx_stream; } ;

/* Variables and functions */
 int amdtp_am824_set_parameters (struct amdtp_stream*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdtp_stream_get_max_payload (struct amdtp_stream*) ; 
 int cmp_connection_reserve (struct cmp_connection*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int keep_resources(struct snd_bebob *bebob, struct amdtp_stream *stream,
			  unsigned int rate, unsigned int index)
{
	struct snd_bebob_stream_formation *formation;
	struct cmp_connection *conn;
	int err;

	if (stream == &bebob->tx_stream) {
		formation = bebob->tx_stream_formations + index;
		conn = &bebob->out_conn;
	} else {
		formation = bebob->rx_stream_formations + index;
		conn = &bebob->in_conn;
	}

	err = amdtp_am824_set_parameters(stream, rate, formation->pcm,
					 formation->midi, false);
	if (err < 0)
		return err;

	return cmp_connection_reserve(conn, amdtp_stream_get_max_payload(stream));
}