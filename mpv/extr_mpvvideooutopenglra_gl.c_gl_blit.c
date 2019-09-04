#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ra_tex_gl {int /*<<< orphan*/  fbo; } ;
struct TYPE_4__ {int /*<<< orphan*/  blit_dst; int /*<<< orphan*/  blit_src; } ;
struct ra_tex {struct ra_tex_gl* priv; TYPE_1__ params; } ;
struct ra {int dummy; } ;
struct mp_rect {int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; int /*<<< orphan*/  y0; int /*<<< orphan*/  x0; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* BindFramebuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BlitFramebuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_DRAW_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_READ_FRAMEBUFFER ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* ra_gl_get (struct ra*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gl_blit(struct ra *ra, struct ra_tex *dst, struct ra_tex *src,
                    struct mp_rect *dst_rc, struct mp_rect *src_rc)
{
    GL *gl = ra_gl_get(ra);

    assert(src->params.blit_src);
    assert(dst->params.blit_dst);

    struct ra_tex_gl *src_gl = src->priv;
    struct ra_tex_gl *dst_gl = dst->priv;

    gl->BindFramebuffer(GL_READ_FRAMEBUFFER, src_gl->fbo);
    gl->BindFramebuffer(GL_DRAW_FRAMEBUFFER, dst_gl->fbo);
    gl->BlitFramebuffer(src_rc->x0, src_rc->y0, src_rc->x1, src_rc->y1,
                        dst_rc->x0, dst_rc->y0, dst_rc->x1, dst_rc->y1,
                        GL_COLOR_BUFFER_BIT, GL_NEAREST);
    gl->BindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    gl->BindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}