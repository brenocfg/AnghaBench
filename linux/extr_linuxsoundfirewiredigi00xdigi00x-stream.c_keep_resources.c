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
struct TYPE_4__ {int channel; } ;
struct snd_dg00x {int /*<<< orphan*/  unit; TYPE_2__ rx_resources; TYPE_2__ tx_resources; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_stream; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  max_speed; } ;

/* Variables and functions */
 scalar_t__ DG00X_ADDR_BASE ; 
 scalar_t__ DG00X_OFFSET_ISOC_CHANNELS ; 
 int EINVAL ; 
 unsigned int SND_DG00X_RATE_COUNT ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 int amdtp_dot_set_parameters (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdtp_stream_get_max_payload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int fw_iso_resources_allocate (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* fw_parent_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_resources (struct snd_dg00x*) ; 
 int /*<<< orphan*/ * snd_dg00x_stream_pcm_channels ; 
 unsigned int* snd_dg00x_stream_rates ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int keep_resources(struct snd_dg00x *dg00x, unsigned int rate)
{
	unsigned int i;
	__be32 data;
	int err;

	/* Check sampling rate. */
	for (i = 0; i < SND_DG00X_RATE_COUNT; i++) {
		if (snd_dg00x_stream_rates[i] == rate)
			break;
	}
	if (i == SND_DG00X_RATE_COUNT)
		return -EINVAL;

	/* Keep resources for out-stream. */
	err = amdtp_dot_set_parameters(&dg00x->rx_stream, rate,
				       snd_dg00x_stream_pcm_channels[i]);
	if (err < 0)
		return err;
	err = fw_iso_resources_allocate(&dg00x->rx_resources,
				amdtp_stream_get_max_payload(&dg00x->rx_stream),
				fw_parent_device(dg00x->unit)->max_speed);
	if (err < 0)
		return err;

	/* Keep resources for in-stream. */
	err = amdtp_dot_set_parameters(&dg00x->tx_stream, rate,
				       snd_dg00x_stream_pcm_channels[i]);
	if (err < 0)
		return err;
	err = fw_iso_resources_allocate(&dg00x->tx_resources,
				amdtp_stream_get_max_payload(&dg00x->tx_stream),
				fw_parent_device(dg00x->unit)->max_speed);
	if (err < 0)
		goto error;

	/* Register isochronous channels for both direction. */
	data = cpu_to_be32((dg00x->tx_resources.channel << 16) |
			   dg00x->rx_resources.channel);
	err = snd_fw_transaction(dg00x->unit, TCODE_WRITE_QUADLET_REQUEST,
				 DG00X_ADDR_BASE + DG00X_OFFSET_ISOC_CHANNELS,
				 &data, sizeof(data), 0);
	if (err < 0)
		goto error;

	return 0;
error:
	release_resources(dg00x);
	return err;
}