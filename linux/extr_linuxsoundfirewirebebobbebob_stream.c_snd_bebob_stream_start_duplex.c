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
struct snd_bebob_rate_spec {int (* get ) (struct snd_bebob*,unsigned int*) ;int (* set ) (struct snd_bebob*,unsigned int) ;} ;
struct snd_bebob {scalar_t__ substreams_counter; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; TYPE_2__* unit; int /*<<< orphan*/ * maudio_special_quirk; TYPE_1__* spec; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {struct snd_bebob_rate_spec* rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK_TIMEOUT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  amdtp_stream_running (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_wait_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ amdtp_streaming_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  break_both_connections (struct snd_bebob*) ; 
 int check_connection_used_by_others (struct snd_bebob*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int make_both_connections (struct snd_bebob*,unsigned int) ; 
 int start_stream (struct snd_bebob*,int /*<<< orphan*/ *,unsigned int) ; 
 int stub1 (struct snd_bebob*,unsigned int*) ; 
 int stub2 (struct snd_bebob*,unsigned int) ; 
 int stub3 (struct snd_bebob*,unsigned int) ; 

int snd_bebob_stream_start_duplex(struct snd_bebob *bebob, unsigned int rate)
{
	const struct snd_bebob_rate_spec *rate_spec = bebob->spec->rate;
	unsigned int curr_rate;
	int err = 0;

	/* Need no substreams */
	if (bebob->substreams_counter == 0)
		goto end;

	/*
	 * Considering JACK/FFADO streaming:
	 * TODO: This can be removed hwdep functionality becomes popular.
	 */
	err = check_connection_used_by_others(bebob, &bebob->rx_stream);
	if (err < 0)
		goto end;

	/*
	 * packet queueing error or detecting discontinuity
	 *
	 * At bus reset, connections should not be broken here. So streams need
	 * to be re-started. This is a reason to use SKIP_INIT_DBC_CHECK flag.
	 */
	if (amdtp_streaming_error(&bebob->rx_stream))
		amdtp_stream_stop(&bebob->rx_stream);
	if (amdtp_streaming_error(&bebob->tx_stream))
		amdtp_stream_stop(&bebob->tx_stream);
	if (!amdtp_stream_running(&bebob->rx_stream) &&
	    !amdtp_stream_running(&bebob->tx_stream))
		break_both_connections(bebob);

	/* stop streams if rate is different */
	err = rate_spec->get(bebob, &curr_rate);
	if (err < 0) {
		dev_err(&bebob->unit->device,
			"fail to get sampling rate: %d\n", err);
		goto end;
	}
	if (rate == 0)
		rate = curr_rate;
	if (rate != curr_rate) {
		amdtp_stream_stop(&bebob->rx_stream);
		amdtp_stream_stop(&bebob->tx_stream);
		break_both_connections(bebob);
	}

	/* master should be always running */
	if (!amdtp_stream_running(&bebob->rx_stream)) {
		/*
		 * NOTE:
		 * If establishing connections at first, Yamaha GO46
		 * (and maybe Terratec X24) don't generate sound.
		 *
		 * For firmware customized by M-Audio, refer to next NOTE.
		 */
		if (bebob->maudio_special_quirk == NULL) {
			err = rate_spec->set(bebob, rate);
			if (err < 0) {
				dev_err(&bebob->unit->device,
					"fail to set sampling rate: %d\n",
					err);
				goto end;
			}
		}

		err = make_both_connections(bebob, rate);
		if (err < 0)
			goto end;

		err = start_stream(bebob, &bebob->rx_stream, rate);
		if (err < 0) {
			dev_err(&bebob->unit->device,
				"fail to run AMDTP master stream:%d\n", err);
			break_both_connections(bebob);
			goto end;
		}

		/*
		 * NOTE:
		 * The firmware customized by M-Audio uses these commands to
		 * start transmitting stream. This is not usual way.
		 */
		if (bebob->maudio_special_quirk != NULL) {
			err = rate_spec->set(bebob, rate);
			if (err < 0) {
				dev_err(&bebob->unit->device,
					"fail to ensure sampling rate: %d\n",
					err);
				amdtp_stream_stop(&bebob->rx_stream);
				break_both_connections(bebob);
				goto end;
			}
		}

		/* wait first callback */
		if (!amdtp_stream_wait_callback(&bebob->rx_stream,
						CALLBACK_TIMEOUT)) {
			amdtp_stream_stop(&bebob->rx_stream);
			break_both_connections(bebob);
			err = -ETIMEDOUT;
			goto end;
		}
	}

	/* start slave if needed */
	if (!amdtp_stream_running(&bebob->tx_stream)) {
		err = start_stream(bebob, &bebob->tx_stream, rate);
		if (err < 0) {
			dev_err(&bebob->unit->device,
				"fail to run AMDTP slave stream:%d\n", err);
			amdtp_stream_stop(&bebob->rx_stream);
			break_both_connections(bebob);
			goto end;
		}

		/* wait first callback */
		if (!amdtp_stream_wait_callback(&bebob->tx_stream,
						CALLBACK_TIMEOUT)) {
			amdtp_stream_stop(&bebob->tx_stream);
			amdtp_stream_stop(&bebob->rx_stream);
			break_both_connections(bebob);
			err = -ETIMEDOUT;
		}
	}
end:
	return err;
}