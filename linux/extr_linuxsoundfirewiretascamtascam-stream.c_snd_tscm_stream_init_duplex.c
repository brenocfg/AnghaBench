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
struct snd_tscm {int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  unit; int /*<<< orphan*/  tx_stream; TYPE_1__* spec; int /*<<< orphan*/  tx_resources; int /*<<< orphan*/  rx_resources; } ;
struct TYPE_2__ {unsigned int pcm_playback_analog_channels; unsigned int pcm_capture_analog_channels; scalar_t__ has_spdif; scalar_t__ has_adat; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDTP_IN_STREAM ; 
 int /*<<< orphan*/  AMDTP_OUT_STREAM ; 
 int /*<<< orphan*/  amdtp_stream_destroy (int /*<<< orphan*/ *) ; 
 int amdtp_tscm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int fw_iso_resources_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int snd_tscm_stream_init_duplex(struct snd_tscm *tscm)
{
	unsigned int pcm_channels;
	int err;

	/* For out-stream. */
	err = fw_iso_resources_init(&tscm->rx_resources, tscm->unit);
	if (err < 0)
		return err;
	pcm_channels = tscm->spec->pcm_playback_analog_channels;
	if (tscm->spec->has_adat)
		pcm_channels += 8;
	if (tscm->spec->has_spdif)
		pcm_channels += 2;
	err = amdtp_tscm_init(&tscm->rx_stream, tscm->unit, AMDTP_OUT_STREAM,
			      pcm_channels);
	if (err < 0)
		return err;

	/* For in-stream. */
	err = fw_iso_resources_init(&tscm->tx_resources, tscm->unit);
	if (err < 0)
		return err;
	pcm_channels = tscm->spec->pcm_capture_analog_channels;
	if (tscm->spec->has_adat)
		pcm_channels += 8;
	if (tscm->spec->has_spdif)
		pcm_channels += 2;
	err = amdtp_tscm_init(&tscm->tx_stream, tscm->unit, AMDTP_IN_STREAM,
			      pcm_channels);
	if (err < 0)
		amdtp_stream_destroy(&tscm->rx_stream);

	return err;
}