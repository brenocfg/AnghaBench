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
struct snd_motu {scalar_t__ capture_substreams; scalar_t__ playback_substreams; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDTP_IN_STREAM ; 
 int /*<<< orphan*/  AMDTP_OUT_STREAM ; 
 int /*<<< orphan*/  destroy_stream (struct snd_motu*,int /*<<< orphan*/ ) ; 

void snd_motu_stream_destroy_duplex(struct snd_motu *motu)
{
	destroy_stream(motu, AMDTP_IN_STREAM);
	destroy_stream(motu, AMDTP_OUT_STREAM);

	motu->playback_substreams = 0;
	motu->capture_substreams = 0;
}