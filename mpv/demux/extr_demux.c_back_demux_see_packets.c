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
struct demux_stream {int back_resuming; scalar_t__ back_resume_dts; scalar_t__ back_resume_pos; int need_wakeup; scalar_t__ back_restarting; scalar_t__ global_correct_pos; scalar_t__ global_correct_dts; struct demux_packet* reader_head; int /*<<< orphan*/  selected; struct demux_internal* in; } ;
struct demux_packet {scalar_t__ dts; scalar_t__ pos; } ;
struct demux_internal {int /*<<< orphan*/  back_demuxing; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct demux_internal*,char*) ; 
 int /*<<< orphan*/  advance_reader_head (struct demux_stream*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  error_on_backward_demuxing (struct demux_internal*) ; 
 int /*<<< orphan*/  find_backward_restart_pos (struct demux_stream*) ; 
 int /*<<< orphan*/  wakeup_ds (struct demux_stream*) ; 

__attribute__((used)) static void back_demux_see_packets(struct demux_stream *ds)
{
    struct demux_internal *in = ds->in;

    if (!ds->selected || !in->back_demuxing)
        return;

    assert(!(ds->back_resuming && ds->back_restarting));

    if (!ds->global_correct_dts && !ds->global_correct_pos) {
        MP_ERR(in, "Can't demux backward due to demuxer problems.\n");
        error_on_backward_demuxing(in);
        return;
    }

    while (ds->back_resuming && ds->reader_head) {
        struct demux_packet *head = ds->reader_head;
        if ((ds->global_correct_dts && head->dts == ds->back_resume_dts) ||
            (ds->global_correct_pos && head->pos == ds->back_resume_pos))
        {
            ds->back_resuming = false;
            ds->need_wakeup = true;
            wakeup_ds(ds); // probably
            break;
        }
        advance_reader_head(ds);
    }

    if (ds->back_restarting)
        find_backward_restart_pos(ds);
}