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
struct gl_video {int num_hwdecs; int /*<<< orphan*/  num_dr_buffers; int /*<<< orphan*/  osd; TYPE_4__* pass_redraw; TYPE_2__* pass_fresh; int /*<<< orphan*/  osd_timer; int /*<<< orphan*/  blit_timer; int /*<<< orphan*/  upload_timer; int /*<<< orphan*/  hdr_peak_ssbo; int /*<<< orphan*/  ra; int /*<<< orphan*/  lut_3d_texture; int /*<<< orphan*/  sc; int /*<<< orphan*/ * hwdecs; } ;
struct TYPE_7__ {struct gl_video* start; } ;
struct TYPE_8__ {TYPE_3__ desc; } ;
struct TYPE_5__ {struct gl_video* start; } ;
struct TYPE_6__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int VO_PASS_PERF_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gc_pending_dr_fences (struct gl_video*,int) ; 
 int /*<<< orphan*/  gl_sc_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpgl_osd_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_buf_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ra_hwdec_uninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_tex_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct gl_video*) ; 
 int /*<<< orphan*/  timer_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uninit_video (struct gl_video*) ; 

void gl_video_uninit(struct gl_video *p)
{
    if (!p)
        return;

    uninit_video(p);

    for (int n = 0; n < p->num_hwdecs; n++)
        ra_hwdec_uninit(p->hwdecs[n]);
    p->num_hwdecs = 0;

    gl_sc_destroy(p->sc);

    ra_tex_free(p->ra, &p->lut_3d_texture);
    ra_buf_free(p->ra, &p->hdr_peak_ssbo);

    timer_pool_destroy(p->upload_timer);
    timer_pool_destroy(p->blit_timer);
    timer_pool_destroy(p->osd_timer);

    for (int i = 0; i < VO_PASS_PERF_MAX; i++) {
        talloc_free(p->pass_fresh[i].desc.start);
        talloc_free(p->pass_redraw[i].desc.start);
    }

    mpgl_osd_destroy(p->osd);

    // Forcibly destroy possibly remaining image references. This should also
    // cause gl_video_dr_free_buffer() to be called for the remaining buffers.
    gc_pending_dr_fences(p, true);

    // Should all have been unreffed already.
    assert(!p->num_dr_buffers);

    talloc_free(p);
}