#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_4__ {void* ring_first_pfn; void* ring_offset; void* ring_size; void* num_pages; void* ring_pt_address; } ;
struct TYPE_3__ {TYPE_2__ ringinfo; } ;
struct sst_hsw_stream {TYPE_1__ request; scalar_t__ commited; } ;
struct sst_hsw {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace_hsw_stream_buffer (struct sst_hsw_stream*) ; 

int sst_hsw_stream_buffer(struct sst_hsw *hsw, struct sst_hsw_stream *stream,
	u32 ring_pt_address, u32 num_pages,
	u32 ring_size, u32 ring_offset, u32 ring_first_pfn)
{
	if (stream->commited) {
		dev_err(hsw->dev, "error: stream committed for buffer\n");
		return -EINVAL;
	}

	stream->request.ringinfo.ring_pt_address = ring_pt_address;
	stream->request.ringinfo.num_pages = num_pages;
	stream->request.ringinfo.ring_size = ring_size;
	stream->request.ringinfo.ring_offset = ring_offset;
	stream->request.ringinfo.ring_first_pfn = ring_first_pfn;

	trace_hsw_stream_buffer(stream);

	return 0;
}