#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  (* p_glDisable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glColorMask ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glLoadIdentity ) () ;int /*<<< orphan*/  (* p_glMatrixMode ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glTexEnvf ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ;int /*<<< orphan*/  (* p_glTexEnvi ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {TYPE_3__ gl; } ;
struct TYPE_8__ {int textures; } ;
struct wined3d_gl_info {scalar_t__* supported; TYPE_4__ gl_ops; TYPE_2__ limits; } ;
struct wined3d_device {int /*<<< orphan*/  shader_priv; TYPE_1__* shader_backend; } ;
struct wined3d_context {scalar_t__ blit_w; scalar_t__ blit_h; scalar_t__* rev_tex_unit_map; void* last_was_rhw; void* last_was_blit; struct wined3d_gl_info* gl_info; } ;
struct TYPE_11__ {scalar_t__ cx; scalar_t__ cy; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* shader_disable ) (int /*<<< orphan*/ ,struct wined3d_context*) ;} ;
typedef  TYPE_5__ SIZE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 size_t ARB_CLIP_CONTROL ; 
 size_t ARB_POINT_SPRITE ; 
 size_t ARB_SAMPLER_OBJECTS ; 
 size_t ARB_TEXTURE_CUBE_MAP ; 
 size_t ARB_TEXTURE_RECTANGLE ; 
 size_t EXT_SECONDARY_COLOR ; 
 size_t EXT_TEXTURE_LOD_BIAS ; 
 int /*<<< orphan*/  GL_ALPHA_TEST ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_COLOR_SUM_EXT ; 
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FOG ; 
 int /*<<< orphan*/  GL_LIGHTING ; 
 int /*<<< orphan*/  GL_LOWER_LEFT ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_NEGATIVE_ONE_TO_ONE ; 
 int /*<<< orphan*/  GL_POINT_SPRITE_ARB ; 
 int /*<<< orphan*/  GL_REPLACE ; 
 int /*<<< orphan*/  GL_SCISSOR_TEST ; 
 int /*<<< orphan*/  GL_STENCIL_TEST ; 
 int /*<<< orphan*/  GL_TEXTURE ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_3D ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_ENV ; 
 int /*<<< orphan*/  GL_TEXTURE_ENV_MODE ; 
 int /*<<< orphan*/  GL_TEXTURE_FILTER_CONTROL_EXT ; 
 int /*<<< orphan*/  GL_TEXTURE_LOD_BIAS_EXT ; 
 int /*<<< orphan*/  GL_TEXTURE_RECTANGLE_ARB ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int MAX_RENDER_TARGETS ; 
 scalar_t__ MAX_TEXTURES ; 
 int /*<<< orphan*/  STATE_RENDER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_SAMPLER (scalar_t__) ; 
 int /*<<< orphan*/  STATE_TEXTURESTAGE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_TRANSFORM (scalar_t__) ; 
 int /*<<< orphan*/  STATE_VDECL ; 
 int /*<<< orphan*/  STATE_VIEWPORT ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 void* TRUE ; 
 size_t WINED3D_GL_LEGACY_CONTEXT ; 
 int /*<<< orphan*/  WINED3D_RS_ALPHABLENDENABLE ; 
 int /*<<< orphan*/  WINED3D_RS_ALPHATESTENABLE ; 
 int /*<<< orphan*/  WINED3D_RS_CLIPPING ; 
 int /*<<< orphan*/  WINED3D_RS_COLORWRITE (int) ; 
 int /*<<< orphan*/  WINED3D_RS_CULLMODE ; 
 int /*<<< orphan*/  WINED3D_RS_FOGENABLE ; 
 int /*<<< orphan*/  WINED3D_RS_LIGHTING ; 
 int /*<<< orphan*/  WINED3D_RS_POINTSPRITEENABLE ; 
 int /*<<< orphan*/  WINED3D_RS_SCISSORTESTENABLE ; 
 int /*<<< orphan*/  WINED3D_RS_SPECULARENABLE ; 
 int /*<<< orphan*/  WINED3D_RS_STENCILENABLE ; 
 int /*<<< orphan*/  WINED3D_RS_ZENABLE ; 
 int /*<<< orphan*/  WINED3D_TSS_COLOR_OP ; 
 scalar_t__ WINED3D_TS_PROJECTION ; 
 scalar_t__ WINED3D_TS_TEXTURE0 ; 
 scalar_t__ WINED3D_TS_WORLD_MATRIX (int /*<<< orphan*/ ) ; 
 scalar_t__ WINED3D_UNMAPPED_STAGE ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  context_active_texture (struct wined3d_context*,struct wined3d_gl_info const*,int) ; 
 int /*<<< orphan*/  context_enable_clip_distances (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_get_rt_size (struct wined3d_context*,TYPE_5__*) ; 
 int /*<<< orphan*/  context_invalidate_state (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindSampler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClipControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisableWINE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_blit_dimension (struct wined3d_gl_info const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 () ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 () ; 
 int /*<<< orphan*/  stub16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub17 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub18 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub19 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub20 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub21 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub22 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub23 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub25 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub26 (int /*<<< orphan*/ ,struct wined3d_context*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SetupForBlit(const struct wined3d_device *device, struct wined3d_context *context)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    DWORD sampler;
    SIZE rt_size;
    int i;

    TRACE("Setting up context %p for blitting\n", context);

    context_get_rt_size(context, &rt_size);

    if (context->last_was_blit)
    {
        if (context->blit_w != rt_size.cx || context->blit_h != rt_size.cy)
        {
            set_blit_dimension(gl_info, rt_size.cx, rt_size.cy);
            context->blit_w = rt_size.cx;
            context->blit_h = rt_size.cy;
            /* No need to dirtify here, the states are still dirtified because
             * they weren't applied since the last SetupForBlit() call. */
        }
        TRACE("Context is already set up for blitting, nothing to do\n");
        return;
    }
    context->last_was_blit = TRUE;

    if (gl_info->supported[WINED3D_GL_LEGACY_CONTEXT])
    {
        /* Disable all textures. The caller can then bind a texture it wants to blit
         * from
         *
         * The blitting code uses (for now) the fixed function pipeline, so make sure to reset all fixed
         * function texture unit. No need to care for higher samplers
         */
        for (i = gl_info->limits.textures - 1; i > 0 ; --i)
        {
            sampler = context->rev_tex_unit_map[i];
            context_active_texture(context, gl_info, i);

            if (gl_info->supported[ARB_TEXTURE_CUBE_MAP])
            {
                gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_CUBE_MAP_ARB);
                checkGLcall("glDisable GL_TEXTURE_CUBE_MAP_ARB");
            }
            gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_3D);
            checkGLcall("glDisable GL_TEXTURE_3D");
            if (gl_info->supported[ARB_TEXTURE_RECTANGLE])
            {
                gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_RECTANGLE_ARB);
                checkGLcall("glDisable GL_TEXTURE_RECTANGLE_ARB");
            }
            gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_2D);
            checkGLcall("glDisable GL_TEXTURE_2D");

            gl_info->gl_ops.gl.p_glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
            checkGLcall("glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);");

            if (sampler != WINED3D_UNMAPPED_STAGE)
            {
                if (sampler < MAX_TEXTURES)
                    context_invalidate_state(context, STATE_TEXTURESTAGE(sampler, WINED3D_TSS_COLOR_OP));
                context_invalidate_state(context, STATE_SAMPLER(sampler));
            }
        }

        context_active_texture(context, gl_info, 0);
        if (gl_info->supported[ARB_TEXTURE_CUBE_MAP])
        {
            gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_CUBE_MAP_ARB);
            checkGLcall("glDisable GL_TEXTURE_CUBE_MAP_ARB");
        }
        gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_3D);
        checkGLcall("glDisable GL_TEXTURE_3D");
        if (gl_info->supported[ARB_TEXTURE_RECTANGLE])
        {
            gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_RECTANGLE_ARB);
            checkGLcall("glDisable GL_TEXTURE_RECTANGLE_ARB");
        }
        gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_2D);
        checkGLcall("glDisable GL_TEXTURE_2D");

        gl_info->gl_ops.gl.p_glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

        gl_info->gl_ops.gl.p_glMatrixMode(GL_TEXTURE);
        checkGLcall("glMatrixMode(GL_TEXTURE)");
        gl_info->gl_ops.gl.p_glLoadIdentity();
        checkGLcall("glLoadIdentity()");

        if (gl_info->supported[EXT_TEXTURE_LOD_BIAS])
        {
            gl_info->gl_ops.gl.p_glTexEnvf(GL_TEXTURE_FILTER_CONTROL_EXT,
                    GL_TEXTURE_LOD_BIAS_EXT, 0.0f);
            checkGLcall("glTexEnvf GL_TEXTURE_LOD_BIAS_EXT ...");
        }

        /* Setup transforms */
        gl_info->gl_ops.gl.p_glMatrixMode(GL_MODELVIEW);
        checkGLcall("glMatrixMode(GL_MODELVIEW)");
        gl_info->gl_ops.gl.p_glLoadIdentity();
        checkGLcall("glLoadIdentity()");
        context_invalidate_state(context, STATE_TRANSFORM(WINED3D_TS_WORLD_MATRIX(0)));

        /* Other misc states */
        gl_info->gl_ops.gl.p_glDisable(GL_ALPHA_TEST);
        checkGLcall("glDisable(GL_ALPHA_TEST)");
        context_invalidate_state(context, STATE_RENDER(WINED3D_RS_ALPHATESTENABLE));
        gl_info->gl_ops.gl.p_glDisable(GL_LIGHTING);
        checkGLcall("glDisable GL_LIGHTING");
        context_invalidate_state(context, STATE_RENDER(WINED3D_RS_LIGHTING));
        glDisableWINE(GL_FOG);
        checkGLcall("glDisable GL_FOG");
        context_invalidate_state(context, STATE_RENDER(WINED3D_RS_FOGENABLE));
    }

    if (gl_info->supported[ARB_SAMPLER_OBJECTS])
        GL_EXTCALL(glBindSampler(0, 0));
    context_active_texture(context, gl_info, 0);

    sampler = context->rev_tex_unit_map[0];
    if (sampler != WINED3D_UNMAPPED_STAGE)
    {
        if (sampler < MAX_TEXTURES)
        {
            context_invalidate_state(context, STATE_TRANSFORM(WINED3D_TS_TEXTURE0 + sampler));
            context_invalidate_state(context, STATE_TEXTURESTAGE(sampler, WINED3D_TSS_COLOR_OP));
        }
        context_invalidate_state(context, STATE_SAMPLER(sampler));
    }

    /* Other misc states */
    gl_info->gl_ops.gl.p_glDisable(GL_DEPTH_TEST);
    checkGLcall("glDisable GL_DEPTH_TEST");
    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_ZENABLE));
    gl_info->gl_ops.gl.p_glDisable(GL_BLEND);
    checkGLcall("glDisable GL_BLEND");
    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_ALPHABLENDENABLE));
    gl_info->gl_ops.gl.p_glDisable(GL_CULL_FACE);
    checkGLcall("glDisable GL_CULL_FACE");
    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_CULLMODE));
    gl_info->gl_ops.gl.p_glDisable(GL_STENCIL_TEST);
    checkGLcall("glDisable GL_STENCIL_TEST");
    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_STENCILENABLE));
    gl_info->gl_ops.gl.p_glDisable(GL_SCISSOR_TEST);
    checkGLcall("glDisable GL_SCISSOR_TEST");
    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_SCISSORTESTENABLE));
    if (gl_info->supported[ARB_POINT_SPRITE])
    {
        gl_info->gl_ops.gl.p_glDisable(GL_POINT_SPRITE_ARB);
        checkGLcall("glDisable GL_POINT_SPRITE_ARB");
        context_invalidate_state(context, STATE_RENDER(WINED3D_RS_POINTSPRITEENABLE));
    }
    gl_info->gl_ops.gl.p_glColorMask(GL_TRUE, GL_TRUE,GL_TRUE,GL_TRUE);
    checkGLcall("glColorMask");
    for (i = 0; i < MAX_RENDER_TARGETS; ++i)
        context_invalidate_state(context, STATE_RENDER(WINED3D_RS_COLORWRITE(i)));
    if (gl_info->supported[EXT_SECONDARY_COLOR])
    {
        gl_info->gl_ops.gl.p_glDisable(GL_COLOR_SUM_EXT);
        context_invalidate_state(context, STATE_RENDER(WINED3D_RS_SPECULARENABLE));
        checkGLcall("glDisable(GL_COLOR_SUM_EXT)");
    }

    context->last_was_rhw = TRUE;
    context_invalidate_state(context, STATE_VDECL); /* because of last_was_rhw = TRUE */

    context_enable_clip_distances(context, 0);
    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_CLIPPING));

    /* FIXME: Make draw_textured_quad() able to work with a upper left origin. */
    if (gl_info->supported[ARB_CLIP_CONTROL])
        GL_EXTCALL(glClipControl(GL_LOWER_LEFT, GL_NEGATIVE_ONE_TO_ONE));

    set_blit_dimension(gl_info, rt_size.cx, rt_size.cy);

    /* Disable shaders */
    device->shader_backend->shader_disable(device->shader_priv, context);

    context->blit_w = rt_size.cx;
    context->blit_h = rt_size.cy;
    context_invalidate_state(context, STATE_VIEWPORT);
    context_invalidate_state(context, STATE_TRANSFORM(WINED3D_TS_PROJECTION));
}