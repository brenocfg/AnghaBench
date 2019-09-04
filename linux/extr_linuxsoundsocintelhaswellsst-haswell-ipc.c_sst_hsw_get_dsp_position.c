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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  read_position_register_address; } ;
struct sst_hsw_stream {TYPE_1__ reply; } ;
struct sst_hsw {int /*<<< orphan*/  dsp; } ;
typedef  int /*<<< orphan*/  rpos ;

/* Variables and functions */
 int /*<<< orphan*/  sst_dsp_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

u32 sst_hsw_get_dsp_position(struct sst_hsw *hsw,
	struct sst_hsw_stream *stream)
{
	u32 rpos;

	sst_dsp_read(hsw->dsp, &rpos,
		stream->reply.read_position_register_address, sizeof(rpos));

	return rpos;
}