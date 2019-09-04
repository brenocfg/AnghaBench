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
struct snd_dg00x {int /*<<< orphan*/  unit; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  tx_resources; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  rx_resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDTP_IN_STREAM ; 
 int /*<<< orphan*/  AMDTP_OUT_STREAM ; 
 int amdtp_dot_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fw_iso_resources_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_dg00x_stream_destroy_duplex (struct snd_dg00x*) ; 

int snd_dg00x_stream_init_duplex(struct snd_dg00x *dg00x)
{
	int err;

	/* For out-stream. */
	err = fw_iso_resources_init(&dg00x->rx_resources, dg00x->unit);
	if (err < 0)
		goto error;
	err = amdtp_dot_init(&dg00x->rx_stream, dg00x->unit, AMDTP_OUT_STREAM);
	if (err < 0)
		goto error;

	/* For in-stream. */
	err = fw_iso_resources_init(&dg00x->tx_resources, dg00x->unit);
	if (err < 0)
		goto error;
	err = amdtp_dot_init(&dg00x->tx_stream, dg00x->unit, AMDTP_IN_STREAM);
	if (err < 0)
		goto error;

	return 0;
error:
	snd_dg00x_stream_destroy_duplex(dg00x);
	return err;
}