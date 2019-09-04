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
struct fw_iso_resources {int /*<<< orphan*/  channel; } ;
struct amdtp_stream {int dummy; } ;
struct snd_motu {int /*<<< orphan*/  unit; struct fw_iso_resources tx_resources; struct fw_iso_resources rx_resources; struct amdtp_stream rx_stream; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK_TIMEOUT ; 
 int ETIMEDOUT ; 
 int amdtp_stream_start (struct amdtp_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdtp_stream_stop (struct amdtp_stream*) ; 
 int /*<<< orphan*/  amdtp_stream_wait_callback (struct amdtp_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_iso_resources_free (struct fw_iso_resources*) ; 
 TYPE_1__* fw_parent_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_isoc_ctx(struct snd_motu *motu, struct amdtp_stream *stream)
{
	struct fw_iso_resources *resources;
	int err;

	if (stream == &motu->rx_stream)
		resources = &motu->rx_resources;
	else
		resources = &motu->tx_resources;

	err = amdtp_stream_start(stream, resources->channel,
				 fw_parent_device(motu->unit)->max_speed);
	if (err < 0)
		return err;

	if (!amdtp_stream_wait_callback(stream, CALLBACK_TIMEOUT)) {
		amdtp_stream_stop(stream);
		fw_iso_resources_free(resources);
		return -ETIMEDOUT;
	}

	return 0;
}