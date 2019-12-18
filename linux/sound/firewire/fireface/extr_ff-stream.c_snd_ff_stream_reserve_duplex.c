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
struct snd_ff {scalar_t__ substreams_counter; TYPE_2__* spec; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_resources; int /*<<< orphan*/  tx_resources; int /*<<< orphan*/  domain; } ;
typedef  enum snd_ff_stream_mode { ____Placeholder_snd_ff_stream_mode } snd_ff_stream_mode ;
typedef  enum snd_ff_clock_src { ____Placeholder_snd_ff_clock_src } snd_ff_clock_src ;
struct TYPE_4__ {TYPE_1__* protocol; int /*<<< orphan*/ * pcm_playback_channels; int /*<<< orphan*/ * pcm_capture_channels; } ;
struct TYPE_3__ {int (* get_clock ) (struct snd_ff*,unsigned int*,int*) ;int (* allocate_resources ) (struct snd_ff*,unsigned int) ;} ;

/* Variables and functions */
 int CIP_SFC_COUNT ; 
 int EINVAL ; 
 int /*<<< orphan*/  amdtp_domain_stop (int /*<<< orphan*/ *) ; 
 int amdtp_ff_set_parameters (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int* amdtp_rate_table ; 
 int /*<<< orphan*/  finish_session (struct snd_ff*) ; 
 int /*<<< orphan*/  fw_iso_resources_free (int /*<<< orphan*/ *) ; 
 int snd_ff_stream_get_multiplier_mode (int,int*) ; 
 int stub1 (struct snd_ff*,unsigned int*,int*) ; 
 int stub2 (struct snd_ff*,unsigned int) ; 

int snd_ff_stream_reserve_duplex(struct snd_ff *ff, unsigned int rate)
{
	unsigned int curr_rate;
	enum snd_ff_clock_src src;
	int err;

	err = ff->spec->protocol->get_clock(ff, &curr_rate, &src);
	if (err < 0)
		return err;

	if (ff->substreams_counter == 0 || curr_rate != rate) {
		enum snd_ff_stream_mode mode;
		int i;

		amdtp_domain_stop(&ff->domain);
		finish_session(ff);

		fw_iso_resources_free(&ff->tx_resources);
		fw_iso_resources_free(&ff->rx_resources);

		for (i = 0; i < CIP_SFC_COUNT; ++i) {
			if (amdtp_rate_table[i] == rate)
				break;
		}
		if (i >= CIP_SFC_COUNT)
			return -EINVAL;

		err = snd_ff_stream_get_multiplier_mode(i, &mode);
		if (err < 0)
			return err;

		err = amdtp_ff_set_parameters(&ff->tx_stream, rate,
					ff->spec->pcm_capture_channels[mode]);
		if (err < 0)
			return err;

		err = amdtp_ff_set_parameters(&ff->rx_stream, rate,
					ff->spec->pcm_playback_channels[mode]);
		if (err < 0)
			return err;

		err = ff->spec->protocol->allocate_resources(ff, rate);
		if (err < 0)
			return err;
	}

	return 0;
}