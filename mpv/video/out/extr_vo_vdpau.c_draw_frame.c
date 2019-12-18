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
struct vo_frame {int /*<<< orphan*/  duration; int /*<<< orphan*/  pts; int /*<<< orphan*/  current; int /*<<< orphan*/  redraw; } ;
struct vo {struct vdpctx* priv; } ;
struct vdpctx {struct mp_image* current_image; int /*<<< orphan*/  current_duration; int /*<<< orphan*/  current_pts; int /*<<< orphan*/  mpvdp; } ;
struct mp_image {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct vo*,char*) ; 
 int /*<<< orphan*/  check_preemption (struct vo*) ; 
 int /*<<< orphan*/  draw_osd (struct vo*) ; 
 struct mp_image* mp_vdpau_upload_video_surface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ status_ok (struct vo*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 
 int /*<<< orphan*/  video_to_output_surface (struct vo*,struct mp_image*) ; 

__attribute__((used)) static void draw_frame(struct vo *vo, struct vo_frame *frame)
{
    struct vdpctx *vc = vo->priv;

    check_preemption(vo);

    if (frame->current && !frame->redraw) {
        struct mp_image *vdp_mpi =
            mp_vdpau_upload_video_surface(vc->mpvdp, frame->current);
        if (!vdp_mpi)
            MP_ERR(vo, "Could not upload image.\n");

        talloc_free(vc->current_image);
        vc->current_image = vdp_mpi;
    }

    vc->current_pts = frame->pts;
    vc->current_duration = frame->duration;

    if (status_ok(vo)) {
        video_to_output_surface(vo, vc->current_image);
        draw_osd(vo);
    }
}