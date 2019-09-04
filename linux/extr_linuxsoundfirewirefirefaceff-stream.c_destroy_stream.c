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
struct snd_ff {int /*<<< orphan*/  rx_resources; int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  tx_resources; int /*<<< orphan*/  tx_stream; } ;
typedef  enum amdtp_stream_direction { ____Placeholder_amdtp_stream_direction } amdtp_stream_direction ;

/* Variables and functions */
 int AMDTP_IN_STREAM ; 
 int /*<<< orphan*/  amdtp_stream_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_iso_resources_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_stream(struct snd_ff *ff, enum amdtp_stream_direction dir)
{
	if (dir == AMDTP_IN_STREAM) {
		amdtp_stream_destroy(&ff->tx_stream);
		fw_iso_resources_destroy(&ff->tx_resources);
	} else {
		amdtp_stream_destroy(&ff->rx_stream);
		fw_iso_resources_destroy(&ff->rx_resources);
	}
}