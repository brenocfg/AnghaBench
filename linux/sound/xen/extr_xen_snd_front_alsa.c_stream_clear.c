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
struct xen_snd_front_pcm_stream_info {int is_open; scalar_t__ num_pages; int /*<<< orphan*/ * pages; scalar_t__ buffer_sz; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  shbuf; int /*<<< orphan*/  evt_pair; int /*<<< orphan*/  hw_ptr; scalar_t__ out_frames; scalar_t__ be_cur_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xen_snd_front_evtchnl_pair_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stream_clear(struct xen_snd_front_pcm_stream_info *stream)
{
	stream->is_open = false;
	stream->be_cur_frame = 0;
	stream->out_frames = 0;
	atomic_set(&stream->hw_ptr, 0);
	xen_snd_front_evtchnl_pair_clear(stream->evt_pair);
	memset(&stream->shbuf, 0, sizeof(stream->shbuf));
	stream->buffer = NULL;
	stream->buffer_sz = 0;
	stream->pages = NULL;
	stream->num_pages = 0;
}