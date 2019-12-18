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
struct ra_tex_upload_params {void* src; int /*<<< orphan*/  stride; struct mp_rect* rc; scalar_t__ invalidate; scalar_t__ buf_offset; struct ra_buf* buf; struct ra_tex* tex; } ;
struct ra_tex_gl {int /*<<< orphan*/  target; int /*<<< orphan*/  type; int /*<<< orphan*/  format; int /*<<< orphan*/  internal_format; int /*<<< orphan*/  texture; int /*<<< orphan*/  pbo; } ;
struct TYPE_6__ {int host_mutable; int dimensions; int /*<<< orphan*/  d; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct ra_tex {TYPE_1__ params; struct ra_tex_gl* priv; } ;
struct ra_buf_gl {int /*<<< orphan*/  fence; int /*<<< orphan*/  buffer; } ;
struct TYPE_7__ {scalar_t__ host_mapped; } ;
struct ra_buf {TYPE_2__ params; struct ra_buf_gl* priv; } ;
struct ra {scalar_t__ use_pbo; } ;
struct mp_rect {scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* FenceSync ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* DeleteSync ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BindBuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* PixelStorei ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* TexImage3D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ;int /*<<< orphan*/  (* TexImage1D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ;int /*<<< orphan*/  (* InvalidateTexImage ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  GL_PIXEL_UNPACK_BUFFER ; 
 int /*<<< orphan*/  GL_SYNC_GPU_COMMANDS_COMPLETE ; 
 int /*<<< orphan*/  GL_TEXTURE_3D ; 
 int /*<<< orphan*/  GL_UNPACK_ALIGNMENT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gl_upload_tex (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_3__* ra_gl_get (struct ra*) ; 
 int ra_tex_upload_pbo (struct ra*,int /*<<< orphan*/ *,struct ra_tex_upload_params const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gl_tex_upload(struct ra *ra,
                          const struct ra_tex_upload_params *params)
{
    GL *gl = ra_gl_get(ra);
    struct ra_tex *tex = params->tex;
    struct ra_buf *buf = params->buf;
    struct ra_tex_gl *tex_gl = tex->priv;
    struct ra_buf_gl *buf_gl = buf ? buf->priv : NULL;
    assert(tex->params.host_mutable);
    assert(!params->buf || !params->src);

    if (ra->use_pbo && !params->buf)
        return ra_tex_upload_pbo(ra, &tex_gl->pbo, params);

    const void *src = params->src;
    if (buf) {
        gl->BindBuffer(GL_PIXEL_UNPACK_BUFFER, buf_gl->buffer);
        src = (void *)params->buf_offset;
    }

    gl->BindTexture(tex_gl->target, tex_gl->texture);
    if (params->invalidate && gl->InvalidateTexImage)
        gl->InvalidateTexImage(tex_gl->texture, 0);

    switch (tex->params.dimensions) {
    case 1:
        gl->TexImage1D(tex_gl->target, 0, tex_gl->internal_format,
                       tex->params.w, 0, tex_gl->format, tex_gl->type, src);
        break;
    case 2: {
        struct mp_rect rc = {0, 0, tex->params.w, tex->params.h};
        if (params->rc)
            rc = *params->rc;
        gl_upload_tex(gl, tex_gl->target, tex_gl->format, tex_gl->type,
                      src, params->stride, rc.x0, rc.y0, rc.x1 - rc.x0,
                      rc.y1 - rc.y0);
        break;
    }
    case 3:
        gl->PixelStorei(GL_UNPACK_ALIGNMENT, 1);
        gl->TexImage3D(GL_TEXTURE_3D, 0, tex_gl->internal_format, tex->params.w,
                       tex->params.h, tex->params.d, 0, tex_gl->format,
                       tex_gl->type, src);
        gl->PixelStorei(GL_UNPACK_ALIGNMENT, 4);
        break;
    }

    gl->BindTexture(tex_gl->target, 0);

    if (buf) {
        gl->BindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
        if (buf->params.host_mapped) {
            // Make sure the PBO is not reused until GL is done with it. If a
            // previous operation is pending, "update" it by creating a new
            // fence that will cover the previous operation as well.
            gl->DeleteSync(buf_gl->fence);
            buf_gl->fence = gl->FenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
        }
    }

    return true;
}