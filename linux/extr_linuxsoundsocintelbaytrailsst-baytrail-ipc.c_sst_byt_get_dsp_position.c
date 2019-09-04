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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ lpe; } ;
struct sst_dsp {TYPE_1__ addr; } ;
struct sst_byt_tstamp {int /*<<< orphan*/  ring_buffer_counter; } ;
struct sst_byt_stream {int str_id; } ;
struct sst_byt {struct sst_dsp* dsp; } ;
typedef  int /*<<< orphan*/  fw_tstamp ;

/* Variables and functions */
 scalar_t__ SST_BYT_TIMESTAMP_OFFSET ; 
 int do_div (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy_fromio (struct sst_byt_tstamp*,scalar_t__,int) ; 

int sst_byt_get_dsp_position(struct sst_byt *byt,
			     struct sst_byt_stream *stream, int buffer_size)
{
	struct sst_dsp *sst = byt->dsp;
	struct sst_byt_tstamp fw_tstamp;
	u8 str_id = stream->str_id;
	u32 tstamp_offset;

	tstamp_offset = SST_BYT_TIMESTAMP_OFFSET + str_id * sizeof(fw_tstamp);
	memcpy_fromio(&fw_tstamp,
		      sst->addr.lpe + tstamp_offset, sizeof(fw_tstamp));

	return do_div(fw_tstamp.ring_buffer_counter, buffer_size);
}