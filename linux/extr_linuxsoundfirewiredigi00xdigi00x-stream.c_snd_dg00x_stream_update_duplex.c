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
struct snd_dg00x {int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_resources; int /*<<< orphan*/  tx_resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_iso_resources_update (int /*<<< orphan*/ *) ; 

void snd_dg00x_stream_update_duplex(struct snd_dg00x *dg00x)
{
	fw_iso_resources_update(&dg00x->tx_resources);
	fw_iso_resources_update(&dg00x->rx_resources);

	amdtp_stream_update(&dg00x->tx_stream);
	amdtp_stream_update(&dg00x->rx_stream);
}