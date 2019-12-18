#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  DrawBuffer; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* SetBuffer ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  ReadBuffer; } ;
struct TYPE_17__ {TYPE_3__ Color; TYPE_2__ Driver; TYPE_1__ Pixel; } ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int /*<<< orphan*/  GLsizei ;
typedef  int /*<<< orphan*/  GLint ;
typedef  int GLenum ;
typedef  TYPE_4__ GLcontext ;

/* Variables and functions */
#define  GL_ALPHA 140 
#define  GL_BGRA_EXT 139 
#define  GL_BGR_EXT 138 
#define  GL_BLUE 137 
#define  GL_COLOR_INDEX 136 
#define  GL_DEPTH_COMPONENT 135 
#define  GL_GREEN 134 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_LUMINANCE 133 
#define  GL_LUMINANCE_ALPHA 132 
#define  GL_RED 131 
#define  GL_RGB 130 
#define  GL_RGBA 129 
#define  GL_STENCIL_INDEX 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_4__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  read_color_pixels (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_depth_pixels (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_index_pixels (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_stencil_pixels (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ ) ; 

void gl_ReadPixels( GLcontext *ctx,
                    GLint x, GLint y, GLsizei width, GLsizei height,
		    GLenum format, GLenum type, GLvoid *pixels )
{
    if (INSIDE_BEGIN_END(ctx))
    {
        gl_error(ctx, GL_INVALID_OPERATION, "glReadPixels");
        return;
    }

    (void) (*ctx->Driver.SetBuffer)(ctx, ctx->Pixel.ReadBuffer);

    switch (format)
    {
    case GL_COLOR_INDEX:
        read_index_pixels(ctx, x, y, width, height, type, pixels);
        break;
    case GL_STENCIL_INDEX:
        read_stencil_pixels(ctx, x, y, width, height, type, pixels);
        break;
    case GL_DEPTH_COMPONENT:
        read_depth_pixels(ctx, x, y, width, height, type, pixels);
        break;
    case GL_RED:
    case GL_GREEN:
    case GL_BLUE:
    case GL_ALPHA:
    case GL_RGB:
    case GL_BGR_EXT:
    case GL_LUMINANCE:
    case GL_LUMINANCE_ALPHA:
    case GL_RGBA:
    case GL_BGRA_EXT:
        read_color_pixels(ctx, x, y, width, height, format, type, pixels);
        break;
    default:
        gl_error(ctx, GL_INVALID_ENUM, "glReadPixels(format)");
    }

    (void) (*ctx->Driver.SetBuffer)(ctx, ctx->Color.DrawBuffer);
}