#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_bebob {int connected; int /*<<< orphan*/  out_conn; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  in_conn; int /*<<< orphan*/  tx_stream; TYPE_2__* rx_stream_formations; TYPE_1__* tx_stream_formations; } ;
struct TYPE_4__ {int pcm; int midi; } ;
struct TYPE_3__ {int pcm; int midi; } ;

/* Variables and functions */
 int amdtp_am824_set_parameters (int /*<<< orphan*/ *,unsigned int,int,int,int) ; 
 int /*<<< orphan*/  amdtp_stream_get_max_payload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmp_connection_break (int /*<<< orphan*/ *) ; 
 int cmp_connection_establish (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int get_formation_index (unsigned int,int*) ; 

__attribute__((used)) static int
make_both_connections(struct snd_bebob *bebob, unsigned int rate)
{
	int index, pcm_channels, midi_channels, err = 0;

	if (bebob->connected)
		goto end;

	/* confirm params for both streams */
	err = get_formation_index(rate, &index);
	if (err < 0)
		goto end;
	pcm_channels = bebob->tx_stream_formations[index].pcm;
	midi_channels = bebob->tx_stream_formations[index].midi;
	err = amdtp_am824_set_parameters(&bebob->tx_stream, rate,
					 pcm_channels, midi_channels * 8,
					 false);
	if (err < 0)
		goto end;

	pcm_channels = bebob->rx_stream_formations[index].pcm;
	midi_channels = bebob->rx_stream_formations[index].midi;
	err = amdtp_am824_set_parameters(&bebob->rx_stream, rate,
					 pcm_channels, midi_channels * 8,
					 false);
	if (err < 0)
		goto end;

	/* establish connections for both streams */
	err = cmp_connection_establish(&bebob->out_conn,
			amdtp_stream_get_max_payload(&bebob->tx_stream));
	if (err < 0)
		goto end;
	err = cmp_connection_establish(&bebob->in_conn,
			amdtp_stream_get_max_payload(&bebob->rx_stream));
	if (err < 0) {
		cmp_connection_break(&bebob->out_conn);
		goto end;
	}

	bebob->connected = true;
end:
	return err;
}