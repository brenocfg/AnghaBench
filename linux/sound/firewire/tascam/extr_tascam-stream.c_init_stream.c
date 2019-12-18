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
struct fw_iso_resources {int dummy; } ;
struct amdtp_stream {int dummy; } ;
struct snd_tscm {int /*<<< orphan*/  unit; TYPE_1__* spec; struct fw_iso_resources rx_resources; struct fw_iso_resources tx_resources; struct amdtp_stream tx_stream; } ;
typedef  enum amdtp_stream_direction { ____Placeholder_amdtp_stream_direction } amdtp_stream_direction ;
struct TYPE_2__ {unsigned int pcm_capture_analog_channels; unsigned int pcm_playback_analog_channels; scalar_t__ has_spdif; scalar_t__ has_adat; } ;

/* Variables and functions */
 int AMDTP_IN_STREAM ; 
 int AMDTP_OUT_STREAM ; 
 int amdtp_tscm_init (struct amdtp_stream*,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  fw_iso_resources_free (struct fw_iso_resources*) ; 
 int fw_iso_resources_init (struct fw_iso_resources*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_stream(struct snd_tscm *tscm, struct amdtp_stream *s)
{
	struct fw_iso_resources *resources;
	enum amdtp_stream_direction dir;
	unsigned int pcm_channels;
	int err;

	if (s == &tscm->tx_stream) {
		resources = &tscm->tx_resources;
		dir = AMDTP_IN_STREAM;
		pcm_channels = tscm->spec->pcm_capture_analog_channels;
	} else {
		resources = &tscm->rx_resources;
		dir = AMDTP_OUT_STREAM;
		pcm_channels = tscm->spec->pcm_playback_analog_channels;
	}

	if (tscm->spec->has_adat)
		pcm_channels += 8;
	if (tscm->spec->has_spdif)
		pcm_channels += 2;

	err = fw_iso_resources_init(resources, tscm->unit);
	if (err < 0)
		return err;

	err = amdtp_tscm_init(s, tscm->unit, dir, pcm_channels);
	if (err < 0)
		fw_iso_resources_free(resources);

	return err;
}