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
struct demux_stream {int bitrate; int skip_to_keyframe; int attached_picture_added; int last_ret_pos; void* last_ret_dts; scalar_t__ last_br_bytes; void* last_br_ts; void* base_ts; } ;

/* Variables and functions */
 void* MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  ds_clear_reader_queue_state (struct demux_stream*) ; 

__attribute__((used)) static void ds_clear_reader_state(struct demux_stream *ds)
{
    ds_clear_reader_queue_state(ds);

    ds->base_ts = ds->last_br_ts = MP_NOPTS_VALUE;
    ds->last_br_bytes = 0;
    ds->bitrate = -1;
    ds->skip_to_keyframe = false;
    ds->attached_picture_added = false;
    ds->last_ret_pos = -1;
    ds->last_ret_dts = MP_NOPTS_VALUE;
}