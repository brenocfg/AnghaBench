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
struct priv {int /*<<< orphan*/  queue; TYPE_1__* opts; } ;
struct mp_vdpau_mixer_frame {void* current; int /*<<< orphan*/  opts; void** past; void** future; int /*<<< orphan*/  field; } ;
struct TYPE_4__ {scalar_t__ hw_subfmt; } ;
struct mp_image {TYPE_2__ params; void** planes; } ;
struct mp_filter {struct priv* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDP_VIDEO_MIXER_PICTURE_STRUCTURE_BOTTOM_FIELD ; 
 int /*<<< orphan*/  VDP_VIDEO_MIXER_PICTURE_STRUCTURE_FRAME ; 
 int /*<<< orphan*/  VDP_VIDEO_MIXER_PICTURE_STRUCTURE_TOP_FIELD ; 
 int /*<<< orphan*/  mp_refqueue_can_output (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_refqueue_execute_reinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_refqueue_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_refqueue_is_top_field (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_refqueue_should_deint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_refqueue_write_out_pin (int /*<<< orphan*/ ,struct mp_image*) ; 
 struct mp_image* mp_vdpau_mixed_frame_create (int /*<<< orphan*/ ) ; 
 struct mp_vdpau_mixer_frame* mp_vdpau_mixed_frame_get (struct mp_image*) ; 
 void* ref_field (struct priv*,struct mp_vdpau_mixer_frame*,int) ; 

__attribute__((used)) static void vf_vdpaupp_process(struct mp_filter *f)
{
    struct priv *p = f->priv;

    mp_refqueue_execute_reinit(p->queue);

    if (!mp_refqueue_can_output(p->queue))
        return;

    struct mp_image *mpi =
        mp_vdpau_mixed_frame_create(mp_refqueue_get_field(p->queue, 0));
    if (!mpi)
        return; // OOM
    struct mp_vdpau_mixer_frame *frame = mp_vdpau_mixed_frame_get(mpi);

    if (!mp_refqueue_should_deint(p->queue)) {
        frame->field = VDP_VIDEO_MIXER_PICTURE_STRUCTURE_FRAME;
    } else if (mp_refqueue_is_top_field(p->queue)) {
        frame->field = VDP_VIDEO_MIXER_PICTURE_STRUCTURE_TOP_FIELD;
    } else {
        frame->field = VDP_VIDEO_MIXER_PICTURE_STRUCTURE_BOTTOM_FIELD;
    }

    frame->future[0] = ref_field(p, frame, 1);
    frame->current = ref_field(p, frame, 0);
    frame->past[0] = ref_field(p, frame, -1);
    frame->past[1] = ref_field(p, frame, -2);

    frame->opts = p->opts->opts;

    mpi->planes[3] = (void *)(uintptr_t)frame->current;

    mpi->params.hw_subfmt = 0; // force mixer

    mp_refqueue_write_out_pin(p->queue, mpi);
}