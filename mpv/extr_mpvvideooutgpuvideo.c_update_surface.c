#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct surface {int /*<<< orphan*/  pts; int /*<<< orphan*/  id; int /*<<< orphan*/  tex; } ;
struct mp_image {int /*<<< orphan*/  pts; } ;
struct TYPE_5__ {int /*<<< orphan*/  gamma; } ;
struct TYPE_6__ {TYPE_2__ color; } ;
struct TYPE_4__ {int x1; int x0; int y1; int y0; } ;
struct gl_video {int use_linear; TYPE_3__ image_params; int /*<<< orphan*/  sc; TYPE_1__ dst_rect; } ;

/* Variables and functions */
 int /*<<< orphan*/  finish_pass_tex (struct gl_video*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pass_info_reset (struct gl_video*,int) ; 
 int /*<<< orphan*/  pass_linearize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pass_render_frame (struct gl_video*,struct mp_image*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool update_surface(struct gl_video *p, struct mp_image *mpi,
                           uint64_t id, struct surface *surf, int flags)
{
    int vp_w = p->dst_rect.x1 - p->dst_rect.x0,
        vp_h = p->dst_rect.y1 - p->dst_rect.y0;

    pass_info_reset(p, false);
    if (!pass_render_frame(p, mpi, id, flags))
        return false;

    // Frame blending should always be done in linear light to preserve the
    // overall brightness, otherwise this will result in flashing dark frames
    // because mixing in compressed light artificially darkens the results
    if (!p->use_linear) {
        p->use_linear = true;
        pass_linearize(p->sc, p->image_params.color.gamma);
    }

    finish_pass_tex(p, &surf->tex, vp_w, vp_h);
    surf->id  = id;
    surf->pts = mpi->pts;
    return true;
}