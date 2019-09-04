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
struct fw_iso_resources {int dummy; } ;
struct amdtp_stream {int dummy; } ;
struct snd_motu {struct fw_iso_resources tx_resources; struct fw_iso_resources rx_resources; struct amdtp_stream rx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_stop (struct amdtp_stream*) ; 
 int /*<<< orphan*/  fw_iso_resources_free (struct fw_iso_resources*) ; 

__attribute__((used)) static void stop_isoc_ctx(struct snd_motu *motu, struct amdtp_stream *stream)
{
	struct fw_iso_resources *resources;

	if (stream == &motu->rx_stream)
		resources = &motu->rx_resources;
	else
		resources = &motu->tx_resources;

	amdtp_stream_stop(stream);
	fw_iso_resources_free(resources);
}