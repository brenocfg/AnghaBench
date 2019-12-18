#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct vdp_functions {int /*<<< orphan*/  (* video_mixer_render ) (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void**,uintptr_t,int,void**,TYPE_2__*,uintptr_t,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* video_mixer_destroy ) (void*) ;int /*<<< orphan*/  (* video_surface_get_parameters ) (uintptr_t,scalar_t__*,scalar_t__*,scalar_t__*) ;int /*<<< orphan*/  (* output_surface_render_output_surface ) (uintptr_t,TYPE_2__*,uintptr_t,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;
struct mp_vdpau_mixer_opts {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  member_0; } ;
struct mp_vdpau_mixer_frame {uintptr_t current; void** future; void** past; int /*<<< orphan*/  field; struct mp_vdpau_mixer_opts opts; TYPE_1__ member_0; } ;
struct mp_vdpau_mixer {void* video_mixer; int initialized; scalar_t__ current_w; scalar_t__ current_h; scalar_t__ current_chroma_type; int /*<<< orphan*/  image_params; struct mp_vdpau_mixer_opts opts; scalar_t__ video_eq; int /*<<< orphan*/  preemption_counter; TYPE_9__* ctx; } ;
struct mp_image {scalar_t__ imgfmt; int /*<<< orphan*/  params; scalar_t__* planes; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  int /*<<< orphan*/  VdpStatus ;
struct TYPE_11__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ VdpRect ;
typedef  uintptr_t VdpOutputSurface ;
typedef  scalar_t__ VdpChromaType ;
struct TYPE_12__ {struct vdp_functions vdp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_VDP_ERROR (struct mp_vdpau_mixer*,char*) ; 
 int /*<<< orphan*/  CHECK_VDP_WARNING (struct mp_vdpau_mixer*,char*) ; 
 scalar_t__ IMGFMT_VDPAU ; 
 scalar_t__ IMGFMT_VDPAU_OUTPUT ; 
 int MP_VDP_HISTORY_FRAMES ; 
 void* VDP_INVALID_HANDLE ; 
 int VDP_OUTPUT_SURFACE_RENDER_ROTATE_0 ; 
 int /*<<< orphan*/  VDP_VIDEO_MIXER_PICTURE_STRUCTURE_FRAME ; 
 scalar_t__ create_vdp_mixer (struct mp_vdpau_mixer*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ mp_csp_equalizer_state_changed (scalar_t__) ; 
 int /*<<< orphan*/  mp_image_params_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mp_vdpau_handle_preemption (TYPE_9__*,int /*<<< orphan*/ *) ; 
 struct mp_vdpau_mixer_frame* mp_vdpau_mixed_frame_get (struct mp_image*) ; 
 int /*<<< orphan*/  opts_equal (struct mp_vdpau_mixer_opts*,struct mp_vdpau_mixer_opts*) ; 
 int /*<<< orphan*/  stub1 (uintptr_t,TYPE_2__*,uintptr_t,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (uintptr_t,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  stub3 (void*) ; 
 int /*<<< orphan*/  stub4 (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void**,uintptr_t,int,void**,TYPE_2__*,uintptr_t,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mp_vdpau_mixer_render(struct mp_vdpau_mixer *mixer,
                          struct mp_vdpau_mixer_opts *opts,
                          VdpOutputSurface output, VdpRect *output_rect,
                          struct mp_image *video, VdpRect *video_rect)
{
    struct vdp_functions *vdp = &mixer->ctx->vdp;
    VdpStatus vdp_st;
    VdpRect fallback_rect = {0, 0, video->w, video->h};

    if (!video_rect)
        video_rect = &fallback_rect;

    int pe = mp_vdpau_handle_preemption(mixer->ctx, &mixer->preemption_counter);
    if (pe < 1) {
        mixer->video_mixer = VDP_INVALID_HANDLE;
        if (pe < 0)
            return -1;
    }

    if (video->imgfmt == IMGFMT_VDPAU_OUTPUT) {
        VdpOutputSurface surface = (uintptr_t)video->planes[3];
        int flags = VDP_OUTPUT_SURFACE_RENDER_ROTATE_0;
        vdp_st = vdp->output_surface_render_output_surface(output,
                                                           output_rect,
                                                           surface,
                                                           video_rect,
                                                           NULL, NULL, flags);
        CHECK_VDP_WARNING(mixer, "Error when calling "
                          "vdp_output_surface_render_output_surface");
        return 0;
    }

    if (video->imgfmt != IMGFMT_VDPAU)
        return -1;

    struct mp_vdpau_mixer_frame *frame = mp_vdpau_mixed_frame_get(video);
    struct mp_vdpau_mixer_frame fallback = {{0}};
    if (!frame) {
        frame = &fallback;
        frame->current = (uintptr_t)video->planes[3];
        for (int n = 0; n < MP_VDP_HISTORY_FRAMES; n++)
            frame->past[n] = frame->future[n] = VDP_INVALID_HANDLE;
        frame->field = VDP_VIDEO_MIXER_PICTURE_STRUCTURE_FRAME;
    }

    if (!opts)
        opts = &frame->opts;

    if (mixer->video_mixer == VDP_INVALID_HANDLE)
        mixer->initialized = false;

    if (mixer->video_eq && mp_csp_equalizer_state_changed(mixer->video_eq))
        mixer->initialized = false;

    VdpChromaType s_chroma_type;
    uint32_t s_w, s_h;

    vdp_st = vdp->video_surface_get_parameters(frame->current, &s_chroma_type,
                                               &s_w, &s_h);
    CHECK_VDP_ERROR(mixer, "Error when calling vdp_video_surface_get_parameters");

    if (!mixer->initialized || !opts_equal(opts, &mixer->opts) ||
        !mp_image_params_equal(&video->params, &mixer->image_params) ||
        mixer->current_w != s_w || mixer->current_h != s_h ||
        mixer->current_chroma_type != s_chroma_type)
    {
        mixer->opts = *opts;
        mixer->image_params = video->params;
        if (mixer->video_mixer != VDP_INVALID_HANDLE) {
            vdp_st = vdp->video_mixer_destroy(mixer->video_mixer);
            CHECK_VDP_WARNING(mixer, "Error when calling vdp_video_mixer_destroy");
        }
        mixer->video_mixer = VDP_INVALID_HANDLE;
        mixer->initialized = false;
        if (create_vdp_mixer(mixer, s_chroma_type, s_w, s_h) < 0)
            return -1;
    }

    vdp_st = vdp->video_mixer_render(mixer->video_mixer, VDP_INVALID_HANDLE,
                                     0, frame->field,
                                     MP_VDP_HISTORY_FRAMES, frame->past,
                                     frame->current,
                                     MP_VDP_HISTORY_FRAMES, frame->future,
                                     video_rect,
                                     output, NULL, output_rect,
                                     0, NULL);
    CHECK_VDP_WARNING(mixer, "Error when calling vdp_video_mixer_render");
    return 0;
}