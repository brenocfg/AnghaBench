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
struct amdtp_stream {int dummy; } ;
struct snd_dg00x {int /*<<< orphan*/  rx_resources; int /*<<< orphan*/  tx_resources; struct amdtp_stream tx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_destroy (struct amdtp_stream*) ; 
 int /*<<< orphan*/  fw_iso_resources_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_stream(struct snd_dg00x *dg00x, struct amdtp_stream *s)
{
	amdtp_stream_destroy(s);

	if (s == &dg00x->tx_stream)
		fw_iso_resources_destroy(&dg00x->tx_resources);
	else
		fw_iso_resources_destroy(&dg00x->rx_resources);
}