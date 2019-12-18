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
struct TYPE_5__ {scalar_t__ (* p_glGetError ) () ;int /*<<< orphan*/  (* p_glTexParameteri ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glTexImage2D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* p_glBindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glGenTextures ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* p_glTexImage1D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {TYPE_2__ gl; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* glFramebufferRenderbuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* glRenderbufferStorage ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* glBindRenderbuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* glGenRenderbuffers ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* glFramebufferTexture2D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* glFramebufferTexture3D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* glFramebufferTexture1D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct wined3d_gl_info {TYPE_3__ gl_ops; TYPE_1__ fbo_ops; } ;
typedef  enum wined3d_gl_resource_type { ____Placeholder_wined3d_gl_resource_type } wined3d_gl_resource_type ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_ATTACHMENT0 ; 
 int /*<<< orphan*/  GL_DEPTH_ATTACHMENT ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_RENDERBUFFER ; 
 int /*<<< orphan*/  GL_STENCIL_ATTACHMENT ; 
 int /*<<< orphan*/  GL_TEXTURE_1D ; 
 int /*<<< orphan*/  GL_TEXTURE_3D ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 unsigned int WINED3DFMT_FLAG_DEPTH ; 
 unsigned int WINED3DFMT_FLAG_STENCIL ; 
#define  WINED3D_GL_RES_TYPE_BUFFER 135 
#define  WINED3D_GL_RES_TYPE_COUNT 134 
#define  WINED3D_GL_RES_TYPE_RB 133 
#define  WINED3D_GL_RES_TYPE_TEX_1D 132 
#define  WINED3D_GL_RES_TYPE_TEX_2D 131 
#define  WINED3D_GL_RES_TYPE_TEX_3D 130 
#define  WINED3D_GL_RES_TYPE_TEX_CUBE 129 
#define  WINED3D_GL_RES_TYPE_TEX_RECT 128 
 int /*<<< orphan*/  glTexImage3D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub17 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub18 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub19 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub20 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub21 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub22 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub23 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub25 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub26 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub27 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub28 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub29 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub30 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub31 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub33 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub34 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub35 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub36 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub37 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub38 () ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_gl_type_to_enum (int) ; 

__attribute__((used)) static void create_and_bind_fbo_attachment(const struct wined3d_gl_info *gl_info, unsigned int flags,
        enum wined3d_gl_resource_type d3d_type, GLuint *object, GLenum internal, GLenum format, GLenum type)
{
    GLenum attach_type = flags & WINED3DFMT_FLAG_DEPTH ?
            GL_DEPTH_ATTACHMENT : GL_COLOR_ATTACHMENT0;

    switch (d3d_type)
    {
        case WINED3D_GL_RES_TYPE_TEX_1D:
            gl_info->gl_ops.gl.p_glGenTextures(1, object);
            gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_1D, *object);
            gl_info->gl_ops.gl.p_glTexImage1D(GL_TEXTURE_1D, 0, internal, 16, 0, format, type, NULL);
            gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            gl_info->fbo_ops.glFramebufferTexture1D(GL_FRAMEBUFFER, attach_type, GL_TEXTURE_1D,
                    *object, 0);
            if (flags & WINED3DFMT_FLAG_STENCIL)
                gl_info->fbo_ops.glFramebufferTexture1D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_1D,
                        *object, 0);
            break;

        case WINED3D_GL_RES_TYPE_TEX_2D:
        case WINED3D_GL_RES_TYPE_TEX_RECT:
            gl_info->gl_ops.gl.p_glGenTextures(1, object);
            gl_info->gl_ops.gl.p_glBindTexture(wined3d_gl_type_to_enum(d3d_type), *object);
            gl_info->gl_ops.gl.p_glTexImage2D(wined3d_gl_type_to_enum(d3d_type), 0, internal, 16, 16, 0,
                    format, type, NULL);
            gl_info->gl_ops.gl.p_glTexParameteri(wined3d_gl_type_to_enum(d3d_type), GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            gl_info->gl_ops.gl.p_glTexParameteri(wined3d_gl_type_to_enum(d3d_type), GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            gl_info->fbo_ops.glFramebufferTexture2D(GL_FRAMEBUFFER, attach_type,
                    wined3d_gl_type_to_enum(d3d_type), *object, 0);
            if (flags & WINED3DFMT_FLAG_STENCIL)
                gl_info->fbo_ops.glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT,
                        wined3d_gl_type_to_enum(d3d_type), *object, 0);
            break;

        case WINED3D_GL_RES_TYPE_TEX_3D:
            gl_info->gl_ops.gl.p_glGenTextures(1, object);
            gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_3D, *object);
            GL_EXTCALL(glTexImage3D(GL_TEXTURE_3D, 0, internal, 16, 16, 16, 0, format, type, NULL));
            gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            gl_info->fbo_ops.glFramebufferTexture3D(GL_FRAMEBUFFER, attach_type,
                    GL_TEXTURE_3D, *object, 0, 0);
            if (flags & WINED3DFMT_FLAG_STENCIL)
                gl_info->fbo_ops.glFramebufferTexture3D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT,
                        GL_TEXTURE_3D, *object, 0, 0);
            break;

        case WINED3D_GL_RES_TYPE_TEX_CUBE:
            gl_info->gl_ops.gl.p_glGenTextures(1, object);
            gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, *object);
            gl_info->gl_ops.gl.p_glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB, 0, internal, 16, 16, 0,
                    format, type, NULL);
            gl_info->gl_ops.gl.p_glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB, 0, internal, 16, 16, 0,
                    format, type, NULL);
            gl_info->gl_ops.gl.p_glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB, 0, internal, 16, 16, 0,
                    format, type, NULL);
            gl_info->gl_ops.gl.p_glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB, 0, internal, 16, 16, 0,
                    format, type, NULL);
            gl_info->gl_ops.gl.p_glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB, 0, internal, 16, 16, 0,
                    format, type, NULL);
            gl_info->gl_ops.gl.p_glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB, 0, internal, 16, 16, 0,
                    format, type, NULL);
            gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            gl_info->fbo_ops.glFramebufferTexture2D(GL_FRAMEBUFFER, attach_type,
                    GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB, *object, 0);
            if (flags & WINED3DFMT_FLAG_STENCIL)
                gl_info->fbo_ops.glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT,
                        GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB, *object, 0);
            break;

        case WINED3D_GL_RES_TYPE_RB:
            gl_info->fbo_ops.glGenRenderbuffers(1, object);
            gl_info->fbo_ops.glBindRenderbuffer(GL_RENDERBUFFER, *object);
            gl_info->fbo_ops.glRenderbufferStorage(GL_RENDERBUFFER, internal, 16, 16);
            gl_info->fbo_ops.glFramebufferRenderbuffer(GL_FRAMEBUFFER, attach_type, GL_RENDERBUFFER,
                    *object);
            if (flags & WINED3DFMT_FLAG_STENCIL)
                gl_info->fbo_ops.glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER,
                        *object);
            break;

        case WINED3D_GL_RES_TYPE_BUFFER:
        case WINED3D_GL_RES_TYPE_COUNT:
            break;
    }

    /* Ideally we'd skip all formats already known not to work on textures
     * by checking for WINED3DFMT_FLAG_TEXTURE here. However, we want to
     * know if we can attach WINED3DFMT_P8_UINT textures to FBOs, and this
     * format never has WINED3DFMT_FLAG_TEXTURE set. Instead, swallow GL
     * errors generated by invalid formats. */
    while (gl_info->gl_ops.gl.p_glGetError());
}