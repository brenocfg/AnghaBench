#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ra_tex_params {int dimensions; int render_src; int src_linear; int /*<<< orphan*/  initial_data; struct ra_format const* format; int /*<<< orphan*/  d; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct ra_format {int dummy; } ;
struct lut3d {int /*<<< orphan*/ * size; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {TYPE_1__* mpi; } ;
struct gl_video {int use_lut_3d; int /*<<< orphan*/ * lut_3d_size; TYPE_3__* ra; int /*<<< orphan*/  lut_3d_texture; int /*<<< orphan*/  cms; TYPE_2__ image; } ;
struct AVBufferRef {int dummy; } ;
typedef  enum mp_csp_trc { ____Placeholder_mp_csp_trc } mp_csp_trc ;
typedef  enum mp_csp_prim { ____Placeholder_mp_csp_prim } mp_csp_prim ;
struct TYPE_8__ {int caps; } ;
struct TYPE_6__ {struct AVBufferRef* icc_profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_WARN (struct gl_video*,char*) ; 
 int RA_CAP_TEX_3D ; 
 int /*<<< orphan*/  debug_check_gl (struct gl_video*,char*) ; 
 int /*<<< orphan*/  gl_lcms_get_lut3d (int /*<<< orphan*/ ,struct lut3d**,int,int,struct AVBufferRef*) ; 
 int /*<<< orphan*/  gl_lcms_has_changed (int /*<<< orphan*/ ,int,int,struct AVBufferRef*) ; 
 struct ra_format* ra_find_unorm_format (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  ra_tex_create (TYPE_3__*,struct ra_tex_params*) ; 
 int /*<<< orphan*/  ra_tex_free (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct lut3d*) ; 

__attribute__((used)) static bool gl_video_get_lut3d(struct gl_video *p, enum mp_csp_prim prim,
                               enum mp_csp_trc trc)
{
    if (!p->use_lut_3d)
        return false;

    struct AVBufferRef *icc = NULL;
    if (p->image.mpi)
        icc = p->image.mpi->icc_profile;

    if (p->lut_3d_texture && !gl_lcms_has_changed(p->cms, prim, trc, icc))
        return true;

    // GLES3 doesn't provide filtered 16 bit integer textures
    // GLES2 doesn't even provide 3D textures
    const struct ra_format *fmt = ra_find_unorm_format(p->ra, 2, 4);
    if (!fmt || !(p->ra->caps & RA_CAP_TEX_3D)) {
        p->use_lut_3d = false;
        MP_WARN(p, "Disabling color management (no RGBA16 3D textures).\n");
        return false;
    }

    struct lut3d *lut3d = NULL;
    if (!fmt || !gl_lcms_get_lut3d(p->cms, &lut3d, prim, trc, icc) || !lut3d) {
        p->use_lut_3d = false;
        return false;
    }

    ra_tex_free(p->ra, &p->lut_3d_texture);

    struct ra_tex_params params = {
        .dimensions = 3,
        .w = lut3d->size[0],
        .h = lut3d->size[1],
        .d = lut3d->size[2],
        .format = fmt,
        .render_src = true,
        .src_linear = true,
        .initial_data = lut3d->data,
    };
    p->lut_3d_texture = ra_tex_create(p->ra, &params);

    debug_check_gl(p, "after 3d lut creation");

    for (int i = 0; i < 3; i++)
        p->lut_3d_size[i] = lut3d->size[i];

    talloc_free(lut3d);

    return true;
}