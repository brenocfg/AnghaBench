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
struct vo_internal {int hasframe; int hasframe_rendered; TYPE_1__* current_frame; int /*<<< orphan*/  current_frame_id; int /*<<< orphan*/ * frame_queued; scalar_t__ delayed_count; scalar_t__ drop_count; } ;
struct vo {struct vo_internal* in; } ;
struct TYPE_2__ {int display_synced; scalar_t__ num_vsyncs; } ;

/* Variables and functions */
 scalar_t__ VO_MAX_REQ_FRAMES ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void forget_frames(struct vo *vo)
{
    struct vo_internal *in = vo->in;
    in->hasframe = false;
    in->hasframe_rendered = false;
    in->drop_count = 0;
    in->delayed_count = 0;
    talloc_free(in->frame_queued);
    in->frame_queued = NULL;
    in->current_frame_id += VO_MAX_REQ_FRAMES + 1;
    // don't unref current_frame; we always want to be able to redraw it
    if (in->current_frame) {
        in->current_frame->num_vsyncs = 0; // but reset future repeats
        in->current_frame->display_synced = false; // mark discontinuity
    }
}