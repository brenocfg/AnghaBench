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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * volume_register_address; } ;
struct sst_hsw_stream {TYPE_1__ reply; } ;
struct sst_hsw {int /*<<< orphan*/  dsp; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  sst_dsp_read (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 

int sst_hsw_stream_get_volume(struct sst_hsw *hsw, struct sst_hsw_stream *stream,
	u32 stage_id, u32 channel, u32 *volume)
{
	if (channel > 1)
		return -EINVAL;

	sst_dsp_read(hsw->dsp, volume,
		stream->reply.volume_register_address[channel],
		sizeof(*volume));

	return 0;
}