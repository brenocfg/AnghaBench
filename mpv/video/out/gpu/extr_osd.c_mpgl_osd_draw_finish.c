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
struct vertex {int dummy; } ;
struct ra_fbo {int /*<<< orphan*/  tex; } ;
struct mpgl_osd_part {size_t format; scalar_t__ num_vertices; int /*<<< orphan*/  vertices; } ;
struct TYPE_2__ {int w; int h; } ;
struct mpgl_osd {TYPE_1__ osd_res; int /*<<< orphan*/  stereo_mode; struct mpgl_osd_part** parts; } ;
struct gl_transform {float* t; float** m; } ;
struct gl_shader_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int** blend_factors ; 
 int /*<<< orphan*/  generate_verts (struct mpgl_osd_part*,struct gl_transform) ; 
 int /*<<< orphan*/  get_3d_side_by_side (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  gl_sc_blend (struct gl_shader_cache*,int const,int const,int const,int const) ; 
 int /*<<< orphan*/  gl_sc_dispatch_draw (struct gl_shader_cache*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gl_transform_ortho_fbo (struct gl_transform*,struct ra_fbo) ; 
 int /*<<< orphan*/  vertex_vao ; 

void mpgl_osd_draw_finish(struct mpgl_osd *ctx, int index,
                          struct gl_shader_cache *sc, struct ra_fbo fbo)
{
    struct mpgl_osd_part *part = ctx->parts[index];

    int div[2];
    get_3d_side_by_side(ctx->stereo_mode, div);

    part->num_vertices = 0;

    for (int x = 0; x < div[0]; x++) {
        for (int y = 0; y < div[1]; y++) {
            struct gl_transform t;
            gl_transform_ortho_fbo(&t, fbo);

            float a_x = ctx->osd_res.w * x;
            float a_y = ctx->osd_res.h * y;
            t.t[0] += a_x * t.m[0][0] + a_y * t.m[1][0];
            t.t[1] += a_x * t.m[0][1] + a_y * t.m[1][1];

            generate_verts(part, t);
        }
    }

    const int *factors = &blend_factors[part->format][0];
    gl_sc_blend(sc, factors[0], factors[1], factors[2], factors[3]);

    gl_sc_dispatch_draw(sc, fbo.tex, false, vertex_vao, MP_ARRAY_SIZE(vertex_vao),
                        sizeof(struct vertex), part->vertices, part->num_vertices);
}