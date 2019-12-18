#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_bebob {scalar_t__ substreams_counter; int /*<<< orphan*/  domain; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_stream; TYPE_3__* unit; TYPE_2__* spec; scalar_t__ maudio_special_quirk; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {TYPE_1__* rate; } ;
struct TYPE_4__ {int (* get ) (struct snd_bebob*,unsigned int*) ;int (* set ) (struct snd_bebob*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK_TIMEOUT ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int amdtp_domain_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_domain_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_running (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_wait_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ amdtp_streaming_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  break_both_connections (struct snd_bebob*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int make_both_connections (struct snd_bebob*) ; 
 int start_stream (struct snd_bebob*,int /*<<< orphan*/ *) ; 
 int stub1 (struct snd_bebob*,unsigned int*) ; 
 int stub2 (struct snd_bebob*,unsigned int) ; 

int snd_bebob_stream_start_duplex(struct snd_bebob *bebob)
{
	int err;

	// Need no substreams.
	if (bebob->substreams_counter == 0)
		return -EIO;

	// packet queueing error or detecting discontinuity
	if (amdtp_streaming_error(&bebob->rx_stream) ||
	    amdtp_streaming_error(&bebob->tx_stream)) {
		amdtp_domain_stop(&bebob->domain);
		break_both_connections(bebob);
	}

	if (!amdtp_stream_running(&bebob->rx_stream)) {
		unsigned int curr_rate;

		if (bebob->maudio_special_quirk) {
			err = bebob->spec->rate->get(bebob, &curr_rate);
			if (err < 0)
				return err;
		}

		err = make_both_connections(bebob);
		if (err < 0)
			return err;

		err = start_stream(bebob, &bebob->rx_stream);
		if (err < 0)
			goto error;

		err = start_stream(bebob, &bebob->tx_stream);
		if (err < 0)
			goto error;

		err = amdtp_domain_start(&bebob->domain);
		if (err < 0)
			goto error;

		// NOTE:
		// The firmware customized by M-Audio uses these commands to
		// start transmitting stream. This is not usual way.
		if (bebob->maudio_special_quirk) {
			err = bebob->spec->rate->set(bebob, curr_rate);
			if (err < 0) {
				dev_err(&bebob->unit->device,
					"fail to ensure sampling rate: %d\n",
					err);
				goto error;
			}
		}

		if (!amdtp_stream_wait_callback(&bebob->rx_stream,
						CALLBACK_TIMEOUT) ||
		    !amdtp_stream_wait_callback(&bebob->tx_stream,
						CALLBACK_TIMEOUT)) {
			err = -ETIMEDOUT;
			goto error;
		}
	}

	return 0;
error:
	amdtp_domain_stop(&bebob->domain);
	break_both_connections(bebob);
	return err;
}