#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_7__ {int sfreq; int num_chan; int pcm_wd_sz; } ;
struct TYPE_6__ {int num_entries; int frag_size; TYPE_1__* ring_buf_info; } ;
struct TYPE_8__ {TYPE_3__ pcm_params; TYPE_2__ frame_info; } ;
struct sst_byt_stream {TYPE_4__ request; } ;
struct sst_byt {int dummy; } ;
struct TYPE_5__ {void* size; void* addr; } ;

/* Variables and functions */

int sst_byt_stream_buffer(struct sst_byt *byt, struct sst_byt_stream *stream,
			  uint32_t buffer_addr, uint32_t buffer_size)
{
	stream->request.frame_info.num_entries = 1;
	stream->request.frame_info.ring_buf_info[0].addr = buffer_addr;
	stream->request.frame_info.ring_buf_info[0].size = buffer_size;
	/* calculate bytes per 4 ms fragment */
	stream->request.frame_info.frag_size =
		stream->request.pcm_params.sfreq *
		stream->request.pcm_params.num_chan *
		stream->request.pcm_params.pcm_wd_sz / 8 *
		4 / 1000;
	return 0;
}