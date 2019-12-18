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
struct TYPE_5__ {scalar_t__ (* p_glGetError ) () ;} ;
struct TYPE_6__ {TYPE_2__ gl; } ;
struct wined3d_gl_info {TYPE_3__ gl_ops; scalar_t__* supported; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct TYPE_4__ {int usage; int /*<<< orphan*/  size; } ;
struct wined3d_buffer {int /*<<< orphan*/  flags; scalar_t__ buffer_object_usage; TYPE_1__ resource; int /*<<< orphan*/  buffer_type_hint; int /*<<< orphan*/  buffer_object; } ;
typedef  scalar_t__ GLenum ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t APPLE_FLUSH_BUFFER_RANGE ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GL_BUFFER_FLUSHING_UNMAP_APPLE ; 
 int /*<<< orphan*/  GL_BUFFER_SERIALIZED_MODIFY_APPLE ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FALSE ; 
 scalar_t__ GL_NO_ERROR ; 
 scalar_t__ GL_STATIC_DRAW ; 
 scalar_t__ GL_STREAM_DRAW_ARB ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int WINED3DUSAGE_DYNAMIC ; 
 int /*<<< orphan*/  WINED3D_BUFFER_APPLESYNC ; 
 int /*<<< orphan*/  WINED3D_BUFFER_USE_BO ; 
 int /*<<< orphan*/  buffer_bind (struct wined3d_buffer*,struct wined3d_context*) ; 
 int /*<<< orphan*/  buffer_clear_dirty_areas (struct wined3d_buffer*) ; 
 int /*<<< orphan*/  buffer_destroy_buffer_object (struct wined3d_buffer*,struct wined3d_context*) ; 
 int /*<<< orphan*/  buffer_invalidate_bo_range (struct wined3d_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  debug_d3dusage (int) ; 
 int /*<<< orphan*/  debug_glerror (scalar_t__) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  glBufferParameteriAPPLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 () ; 
 scalar_t__ stub2 () ; 
 scalar_t__ stub3 () ; 
 scalar_t__ stub4 () ; 

__attribute__((used)) static BOOL buffer_create_buffer_object(struct wined3d_buffer *buffer, struct wined3d_context *context)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    GLenum gl_usage = GL_STATIC_DRAW;
    GLenum error;

    TRACE("Creating an OpenGL buffer object for wined3d_buffer %p with usage %s.\n",
            buffer, debug_d3dusage(buffer->resource.usage));

    /* Make sure that the gl error is cleared. Do not use checkGLcall
     * here because checkGLcall just prints a fixme and continues. However,
     * if an error during VBO creation occurs we can fall back to non-VBO operation
     * with full functionality(but performance loss).
     */
    while (gl_info->gl_ops.gl.p_glGetError() != GL_NO_ERROR);

    /* Basically the FVF parameter passed to CreateVertexBuffer is no good.
     * The vertex declaration from the device determines how the data in the
     * buffer is interpreted. This means that on each draw call the buffer has
     * to be verified to check if the rhw and color values are in the correct
     * format. */

    GL_EXTCALL(glGenBuffers(1, &buffer->buffer_object));
    error = gl_info->gl_ops.gl.p_glGetError();
    if (!buffer->buffer_object || error != GL_NO_ERROR)
    {
        ERR("Failed to create a BO with error %s (%#x).\n", debug_glerror(error), error);
        goto fail;
    }

    buffer_bind(buffer, context);
    error = gl_info->gl_ops.gl.p_glGetError();
    if (error != GL_NO_ERROR)
    {
        ERR("Failed to bind the BO with error %s (%#x).\n", debug_glerror(error), error);
        goto fail;
    }

    if (buffer->resource.usage & WINED3DUSAGE_DYNAMIC)
    {
        TRACE("Buffer has WINED3DUSAGE_DYNAMIC set.\n");
        gl_usage = GL_STREAM_DRAW_ARB;

        if (gl_info->supported[APPLE_FLUSH_BUFFER_RANGE])
        {
            GL_EXTCALL(glBufferParameteriAPPLE(buffer->buffer_type_hint, GL_BUFFER_FLUSHING_UNMAP_APPLE, GL_FALSE));
            GL_EXTCALL(glBufferParameteriAPPLE(buffer->buffer_type_hint, GL_BUFFER_SERIALIZED_MODIFY_APPLE, GL_FALSE));
            checkGLcall("glBufferParameteriAPPLE");
            buffer->flags |= WINED3D_BUFFER_APPLESYNC;
        }
        /* No setup is needed here for GL_ARB_map_buffer_range. */
    }

    GL_EXTCALL(glBufferData(buffer->buffer_type_hint, buffer->resource.size, NULL, gl_usage));
    error = gl_info->gl_ops.gl.p_glGetError();
    if (error != GL_NO_ERROR)
    {
        ERR("glBufferData failed with error %s (%#x).\n", debug_glerror(error), error);
        goto fail;
    }

    buffer->buffer_object_usage = gl_usage;
    buffer_invalidate_bo_range(buffer, 0, 0);

    return TRUE;

fail:
    /* Clean up all BO init, but continue because we can work without a BO :-) */
    ERR("Failed to create a buffer object. Continuing, but performance issues may occur.\n");
    buffer->flags &= ~WINED3D_BUFFER_USE_BO;
    buffer_destroy_buffer_object(buffer, context);
    buffer_clear_dirty_areas(buffer);
    return FALSE;
}