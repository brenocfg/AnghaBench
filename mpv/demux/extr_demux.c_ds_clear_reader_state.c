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
struct demux_stream {int bitrate; int skip_to_keyframe; int attached_picture_added; int last_ret_pos; int back_restart_pos; int back_restart_eof; int back_restarting; int back_resume_pos; int back_resuming; int back_range_started; scalar_t__ back_range_preroll; scalar_t__ back_range_count; void* back_resume_dts; void* back_seek_pos; scalar_t__ eager; TYPE_1__* in; scalar_t__ back_restart_next; void* back_restart_dts; void* last_ret_dts; scalar_t__ last_br_bytes; void* last_br_ts; void* base_ts; } ;
struct TYPE_2__ {scalar_t__ back_demuxing; } ;

/* Variables and functions */
 void* MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  ds_clear_reader_queue_state (struct demux_stream*) ; 

__attribute__((used)) static void ds_clear_reader_state(struct demux_stream *ds,
                                  bool clear_back_state)
{
    ds_clear_reader_queue_state(ds);

    ds->base_ts = ds->last_br_ts = MP_NOPTS_VALUE;
    ds->last_br_bytes = 0;
    ds->bitrate = -1;
    ds->skip_to_keyframe = false;
    ds->attached_picture_added = false;
    ds->last_ret_pos = -1;
    ds->last_ret_dts = MP_NOPTS_VALUE;

    if (clear_back_state) {
        ds->back_restart_pos = -1;
        ds->back_restart_dts = MP_NOPTS_VALUE;
        ds->back_restart_eof = false;
        ds->back_restart_next = ds->in->back_demuxing;
        ds->back_restarting = ds->in->back_demuxing && ds->eager;
        ds->back_seek_pos = MP_NOPTS_VALUE;
        ds->back_resume_pos = -1;
        ds->back_resume_dts = MP_NOPTS_VALUE;
        ds->back_resuming = false;
        ds->back_range_started = false;
        ds->back_range_count = 0;
        ds->back_range_preroll = 0;
    }
}