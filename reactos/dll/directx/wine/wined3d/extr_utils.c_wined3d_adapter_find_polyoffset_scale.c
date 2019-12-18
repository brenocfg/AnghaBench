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
struct wined3d_vec3 {float member_0; float member_1; float member_2; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* p_glDisable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glDeleteTextures ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* p_glGetTexImage ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* p_glBindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glPolygonOffset ) (float,float) ;int /*<<< orphan*/  (* p_glClear ) (int) ;int /*<<< orphan*/  (* p_glViewport ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* p_glEnable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glClearDepth ) (float) ;int /*<<< orphan*/  (* p_glClearColor ) (float,float,float,float) ;int /*<<< orphan*/  (* p_glTexImage2D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glTexParameteri ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glGenTextures ) (int,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {TYPE_2__ gl; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* glBindFramebuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* glDeleteFramebuffers ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* glDeleteRenderbuffers ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* glFramebufferRenderbuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* glFramebufferTexture2D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* glGenFramebuffers ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* glRenderbufferStorage ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* glBindRenderbuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* glGenRenderbuffers ) (int,int /*<<< orphan*/ *) ;} ;
struct wined3d_gl_info {TYPE_3__ gl_ops; TYPE_1__ fbo_ops; } ;
struct wined3d_color {float member_0; float member_1; float member_2; float member_3; } ;
struct wined3d_caps_gl_ctx {struct wined3d_gl_info* gl_info; } ;
struct TYPE_8__ {scalar_t__ offscreen_rendering_mode; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,unsigned int) ; 
 int /*<<< orphan*/  FIXME (char*,unsigned int) ; 
 int /*<<< orphan*/  GL_BGRA ; 
 int /*<<< orphan*/  GL_COLOR_ATTACHMENT0 ; 
 int GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_DEPTH_ATTACHMENT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_POLYGON_OFFSET_FILL ; 
 int /*<<< orphan*/  GL_RENDERBUFFER ; 
 int /*<<< orphan*/  GL_RGBA8 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAX_LEVEL ; 
 int /*<<< orphan*/  GL_UNSIGNED_INT_8_8_8_8_REV ; 
 scalar_t__ ORM_FBO ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  draw_test_quad (struct wined3d_caps_gl_ctx*,struct wined3d_vec3 const*,struct wined3d_color const*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (float,float,float,float) ; 
 int /*<<< orphan*/  stub13 (float) ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub17 (int) ; 
 int /*<<< orphan*/  stub18 (float,float) ; 
 int /*<<< orphan*/  stub19 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub20 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub21 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub22 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub23 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub25 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub26 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub8 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ wined3d_settings ; 

__attribute__((used)) static float wined3d_adapter_find_polyoffset_scale(struct wined3d_caps_gl_ctx *ctx, GLenum format)
{
    const struct wined3d_gl_info *gl_info = ctx->gl_info;
    static const struct wined3d_color blue = {0.0f, 0.0f, 1.0f, 1.0f};
    GLuint fbo, color, depth;
    unsigned int low = 0, high = 32, cur;
    DWORD readback[256];
    static const struct wined3d_vec3 geometry[] =
    {
        {-1.0f, -1.0f, -1.0f},
        { 1.0f, -1.0f,  0.0f},
        {-1.0f,  1.0f, -1.0f},
        { 1.0f,  1.0f,  0.0f},
    };

    /* Most drivers want 2^23 for fixed point depth buffers, including r300g, r600g,
     * Nvidia. Use this as a fallback if the detection fails. */
    unsigned int fallback = 23;

    if (wined3d_settings.offscreen_rendering_mode != ORM_FBO)
    {
        FIXME("No FBOs, assuming polyoffset scale of 2^%u.\n", fallback);
        return (float)(1u << fallback);
    }

    gl_info->gl_ops.gl.p_glGenTextures(1, &color);
    gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_2D, color);
    gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    gl_info->gl_ops.gl.p_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 256, 1, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, 0);

    gl_info->fbo_ops.glGenRenderbuffers(1, &depth);
    gl_info->fbo_ops.glBindRenderbuffer(GL_RENDERBUFFER, depth);
    gl_info->fbo_ops.glRenderbufferStorage(GL_RENDERBUFFER, format, 256, 1);

    gl_info->fbo_ops.glGenFramebuffers(1, &fbo);
    gl_info->fbo_ops.glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    gl_info->fbo_ops.glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color, 0);
    gl_info->fbo_ops.glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth);
    checkGLcall("Setup framebuffer");

    gl_info->gl_ops.gl.p_glClearColor(0.0f, 0.0f, 0.5f, 0.0f);
    gl_info->gl_ops.gl.p_glClearDepth(0.5f);
    gl_info->gl_ops.gl.p_glEnable(GL_DEPTH_TEST);
    gl_info->gl_ops.gl.p_glEnable(GL_POLYGON_OFFSET_FILL);
    gl_info->gl_ops.gl.p_glViewport(0, 0, 256, 1);
    checkGLcall("Misc parameters");

    for (;;)
    {
        if (high - low <= 1)
        {
            ERR("PolygonOffset scale factor detection failed, using fallback value 2^%u.\n", fallback);
            cur = fallback;
            break;
        }
        cur = (low + high) / 2;

        gl_info->gl_ops.gl.p_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        /* The post viewport transform Z of the geometry runs from 0.0 to 0.5. We want to push it another
         * 0.25 so that the Z buffer content (0.5) cuts the quad off at half the screen. */
        gl_info->gl_ops.gl.p_glPolygonOffset(0.0f, (float)(1u << cur) * 0.25f);
        draw_test_quad(ctx, geometry, &blue);
        checkGLcall("Test draw");

        /* Rebinding texture to workaround a fglrx bug. */
        gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_2D, color);
        gl_info->gl_ops.gl.p_glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, readback);
        checkGLcall("readback");

        TRACE("low %02u, high %02u, cur %2u, 0=0x%08x, 125=0x%08x, 131=0x%08x, 255=0x%08x\n",
                low, high, cur, readback[0], readback[125], readback[131], readback[255]);

        if ((readback[125] & 0xff) < 0xa0)
            high = cur;
        else if ((readback[131] & 0xff) > 0xa0)
            low = cur;
        else
        {
            TRACE("Found scale factor 2^%u for format %x.\n", cur, format);
            break;
        }
    }

    gl_info->gl_ops.gl.p_glDeleteTextures(1, &color);
    gl_info->fbo_ops.glDeleteRenderbuffers(1, &depth);
    gl_info->fbo_ops.glDeleteFramebuffers(1, &fbo);
    gl_info->fbo_ops.glBindFramebuffer(GL_FRAMEBUFFER, 0);
    checkGLcall("Delete framebuffer");

    gl_info->gl_ops.gl.p_glDisable(GL_DEPTH_TEST);
    gl_info->gl_ops.gl.p_glDisable(GL_POLYGON_OFFSET_FILL);
    return (float)(1u << cur);
}