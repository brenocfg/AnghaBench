#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int channels_mask; } ;
struct snd_ff {TYPE_3__ tx_resources; int /*<<< orphan*/  unit; int /*<<< orphan*/  rx_stream; TYPE_3__ rx_resources; TYPE_1__* spec; int /*<<< orphan*/  tx_stream; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_speed; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pcm_playback_channels; int /*<<< orphan*/ * pcm_capture_channels; } ;

/* Variables and functions */
 int amdtp_ff_set_parameters (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdtp_stream_get_max_payload (int /*<<< orphan*/ *) ; 
 int fw_iso_resources_allocate (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_iso_resources_free (TYPE_3__*) ; 
 TYPE_2__* fw_parent_device (int /*<<< orphan*/ ) ; 
 int get_rate_mode (unsigned int,int*) ; 

__attribute__((used)) static int keep_resources(struct snd_ff *ff, unsigned int rate)
{
	int mode;
	int err;

	err = get_rate_mode(rate, &mode);
	if (err < 0)
		return err;

	/* Keep resources for in-stream. */
	err = amdtp_ff_set_parameters(&ff->tx_stream, rate,
				      ff->spec->pcm_capture_channels[mode]);
	if (err < 0)
		return err;
	ff->tx_resources.channels_mask = 0x00000000000000ffuLL;
	err = fw_iso_resources_allocate(&ff->tx_resources,
			amdtp_stream_get_max_payload(&ff->tx_stream),
			fw_parent_device(ff->unit)->max_speed);
	if (err < 0)
		return err;

	/* Keep resources for out-stream. */
	err = amdtp_ff_set_parameters(&ff->rx_stream, rate,
				      ff->spec->pcm_playback_channels[mode]);
	if (err < 0)
		return err;
	ff->rx_resources.channels_mask = 0x00000000000000ffuLL;
	err = fw_iso_resources_allocate(&ff->rx_resources,
			amdtp_stream_get_max_payload(&ff->rx_stream),
			fw_parent_device(ff->unit)->max_speed);
	if (err < 0)
		fw_iso_resources_free(&ff->tx_resources);

	return err;
}