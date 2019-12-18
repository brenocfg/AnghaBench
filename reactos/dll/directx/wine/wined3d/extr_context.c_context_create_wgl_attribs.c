#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wined3d_gl_info {int selected_gl_version; int /*<<< orphan*/  (* p_wglCreateContextAttribsARB ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
typedef  int /*<<< orphan*/  HGLRC ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int MAKEDWORD_VERSION (int,int) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int WGL_CONTEXT_DEBUG_BIT_ARB ; 
 int WGL_CONTEXT_FLAGS_ARB ; 
 int WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB ; 
 int WGL_CONTEXT_MAJOR_VERSION_ARB ; 
 int WGL_CONTEXT_MINOR_VERSION_ARB ; 
 scalar_t__ context_debug_output_enabled (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

HGLRC context_create_wgl_attribs(const struct wined3d_gl_info *gl_info, HDC hdc, HGLRC share_ctx)
{
    HGLRC ctx;
    unsigned int ctx_attrib_idx = 0;
    GLint ctx_attribs[7], ctx_flags = 0;

    if (context_debug_output_enabled(gl_info))
        ctx_flags = WGL_CONTEXT_DEBUG_BIT_ARB;
    ctx_attribs[ctx_attrib_idx++] = WGL_CONTEXT_MAJOR_VERSION_ARB;
    ctx_attribs[ctx_attrib_idx++] = gl_info->selected_gl_version >> 16;
    ctx_attribs[ctx_attrib_idx++] = WGL_CONTEXT_MINOR_VERSION_ARB;
    ctx_attribs[ctx_attrib_idx++] = gl_info->selected_gl_version & 0xffff;
    if (gl_info->selected_gl_version >= MAKEDWORD_VERSION(3, 2))
        ctx_flags |= WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;
    if (ctx_flags)
    {
        ctx_attribs[ctx_attrib_idx++] = WGL_CONTEXT_FLAGS_ARB;
        ctx_attribs[ctx_attrib_idx++] = ctx_flags;
    }
    ctx_attribs[ctx_attrib_idx] = 0;

    if (!(ctx = gl_info->p_wglCreateContextAttribsARB(hdc, share_ctx, ctx_attribs)))
    {
        if (ctx_flags & WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB)
        {
            ctx_attribs[ctx_attrib_idx - 1] &= ~WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;
            if (!(ctx = gl_info->p_wglCreateContextAttribsARB(hdc, share_ctx, ctx_attribs)))
                WARN("Failed to create a WGL context with wglCreateContextAttribsARB, last error %#x.\n",
                        GetLastError());
        }
    }
    return ctx;
}