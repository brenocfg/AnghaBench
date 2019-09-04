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
struct snd_dg00x {scalar_t__ substreams_counter; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_session (struct snd_dg00x*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  release_resources (struct snd_dg00x*) ; 

void snd_dg00x_stream_stop_duplex(struct snd_dg00x *dg00x)
{
	if (dg00x->substreams_counter > 0)
		return;

	amdtp_stream_stop(&dg00x->tx_stream);
	amdtp_stream_stop(&dg00x->rx_stream);
	finish_session(dg00x);
	release_resources(dg00x);

	/*
	 * Just after finishing the session, the device may lost transmitting
	 * functionality for a short time.
	 */
	msleep(50);
}