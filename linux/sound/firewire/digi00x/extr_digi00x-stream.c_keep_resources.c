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
struct snd_dg00x {int /*<<< orphan*/  unit; struct fw_iso_resources rx_resources; struct fw_iso_resources tx_resources; struct amdtp_stream tx_stream; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_speed; } ;

/* Variables and functions */
 int EINVAL ; 
 int SND_DG00X_RATE_COUNT ; 
 int amdtp_dot_set_parameters (struct amdtp_stream*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdtp_stream_get_max_payload (struct amdtp_stream*) ; 
 int fw_iso_resources_allocate (struct fw_iso_resources*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* fw_parent_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * snd_dg00x_stream_pcm_channels ; 
 unsigned int* snd_dg00x_stream_rates ; 

__attribute__((used)) static int keep_resources(struct snd_dg00x *dg00x, struct amdtp_stream *stream,
			  unsigned int rate)
{
	struct fw_iso_resources *resources;
	int i;
	int err;

	// Check sampling rate.
	for (i = 0; i < SND_DG00X_RATE_COUNT; i++) {
		if (snd_dg00x_stream_rates[i] == rate)
			break;
	}
	if (i == SND_DG00X_RATE_COUNT)
		return -EINVAL;

	if (stream == &dg00x->tx_stream)
		resources = &dg00x->tx_resources;
	else
		resources = &dg00x->rx_resources;

	err = amdtp_dot_set_parameters(stream, rate,
				       snd_dg00x_stream_pcm_channels[i]);
	if (err < 0)
		return err;

	return fw_iso_resources_allocate(resources,
				amdtp_stream_get_max_payload(stream),
				fw_parent_device(dg00x->unit)->max_speed);
}