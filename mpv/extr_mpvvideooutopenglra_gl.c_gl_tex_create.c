#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ra_tex_params {int dimensions; int /*<<< orphan*/  initial_data; int /*<<< orphan*/  d; int /*<<< orphan*/  h; int /*<<< orphan*/  w; scalar_t__ src_repeat; scalar_t__ src_linear; TYPE_1__* format; } ;
struct ra_tex_gl {int own_objects; int /*<<< orphan*/  texture; int /*<<< orphan*/  fbo; int /*<<< orphan*/  target; int /*<<< orphan*/  type; int /*<<< orphan*/  format; int /*<<< orphan*/  internal_format; } ;
struct TYPE_9__ {TYPE_2__* format; scalar_t__ downloadable; scalar_t__ blit_dst; scalar_t__ blit_src; scalar_t__ render_dst; } ;
struct ra_tex {TYPE_3__ params; struct ra_tex_gl* priv; } ;
struct ra {int /*<<< orphan*/  log; } ;
struct TYPE_10__ {int mpgl_caps; scalar_t__ (* CheckFramebufferStatus ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BindFramebuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* FramebufferTexture2D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GenFramebuffers ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* PixelStorei ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* TexImage3D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* TexImage2D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* TexImage1D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* TexParameteri ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GenTextures ) (int,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  renderable; } ;
struct TYPE_7__ {int /*<<< orphan*/  dummy_format; } ;
typedef  int /*<<< orphan*/  GLint ;
typedef  scalar_t__ GLenum ;
typedef  TYPE_4__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  GL_CLAMP_TO_EDGE ; 
 int /*<<< orphan*/  GL_COLOR_ATTACHMENT0 ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 scalar_t__ GL_FRAMEBUFFER_COMPLETE ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_REPEAT ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_R ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_T ; 
 int /*<<< orphan*/  GL_UNPACK_ALIGNMENT ; 
 int MPGL_CAP_FB ; 
 int /*<<< orphan*/  MP_ERR (struct ra*,char*,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gl_check_error (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 struct ra_tex* gl_tex_create_blank (struct ra*,struct ra_tex_params const*) ; 
 TYPE_4__* ra_gl_get (struct ra*) ; 
 int /*<<< orphan*/  ra_tex_free (struct ra*,struct ra_tex**) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub17 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub18 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ra_tex *gl_tex_create(struct ra *ra,
                                    const struct ra_tex_params *params)
{
    GL *gl = ra_gl_get(ra);
    assert(!params->format->dummy_format);

    struct ra_tex *tex = gl_tex_create_blank(ra, params);
    if (!tex)
        return NULL;
    struct ra_tex_gl *tex_gl = tex->priv;

    tex_gl->own_objects = true;

    gl->GenTextures(1, &tex_gl->texture);
    gl->BindTexture(tex_gl->target, tex_gl->texture);

    GLint filter = params->src_linear ? GL_LINEAR : GL_NEAREST;
    GLint wrap = params->src_repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE;
    gl->TexParameteri(tex_gl->target, GL_TEXTURE_MIN_FILTER, filter);
    gl->TexParameteri(tex_gl->target, GL_TEXTURE_MAG_FILTER, filter);
    gl->TexParameteri(tex_gl->target, GL_TEXTURE_WRAP_S, wrap);
    if (params->dimensions > 1)
        gl->TexParameteri(tex_gl->target, GL_TEXTURE_WRAP_T, wrap);
    if (params->dimensions > 2)
        gl->TexParameteri(tex_gl->target, GL_TEXTURE_WRAP_R, wrap);

    gl->PixelStorei(GL_UNPACK_ALIGNMENT, 1);
    switch (params->dimensions) {
    case 1:
        gl->TexImage1D(tex_gl->target, 0, tex_gl->internal_format, params->w,
                       0, tex_gl->format, tex_gl->type, params->initial_data);
        break;
    case 2:
        gl->TexImage2D(tex_gl->target, 0, tex_gl->internal_format, params->w,
                       params->h, 0, tex_gl->format, tex_gl->type,
                       params->initial_data);
        break;
    case 3:
        gl->TexImage3D(tex_gl->target, 0, tex_gl->internal_format, params->w,
                       params->h, params->d, 0, tex_gl->format, tex_gl->type,
                       params->initial_data);
        break;
    }
    gl->PixelStorei(GL_UNPACK_ALIGNMENT, 4);

    gl->BindTexture(tex_gl->target, 0);

    gl_check_error(gl, ra->log, "after creating texture");

    // Even blitting needs an FBO in OpenGL for strange reasons.
    // Download is handled by reading from an FBO.
    if (tex->params.render_dst || tex->params.blit_src ||
        tex->params.blit_dst || tex->params.downloadable)
    {
        if (!tex->params.format->renderable) {
            MP_ERR(ra, "Trying to create renderable texture with unsupported "
                   "format.\n");
            ra_tex_free(ra, &tex);
            return NULL;
        }

        assert(gl->mpgl_caps & MPGL_CAP_FB);

        gl->GenFramebuffers(1, &tex_gl->fbo);
        gl->BindFramebuffer(GL_FRAMEBUFFER, tex_gl->fbo);
        gl->FramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                 GL_TEXTURE_2D, tex_gl->texture, 0);
        GLenum err = gl->CheckFramebufferStatus(GL_FRAMEBUFFER);
        gl->BindFramebuffer(GL_FRAMEBUFFER, 0);

        if (err != GL_FRAMEBUFFER_COMPLETE) {
            MP_ERR(ra, "Error: framebuffer completeness check failed (error=%d).\n",
                   (int)err);
            ra_tex_free(ra, &tex);
            return NULL;
        }


        gl_check_error(gl, ra->log, "after creating framebuffer");
    }

    return tex;
}