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
struct wined3d_gl_info {int dummy; } ;
struct wined3d_caps_gl_ctx {int /*<<< orphan*/ * restore_gl_ctx; int /*<<< orphan*/ * restore_dc; int /*<<< orphan*/  wnd; int /*<<< orphan*/  dc; int /*<<< orphan*/  gl_ctx; scalar_t__ test_vbo; scalar_t__ test_program_id; struct wined3d_gl_info* gl_info; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  glDeleteBuffers (int,scalar_t__*) ; 
 int /*<<< orphan*/  glDeleteProgram (scalar_t__) ; 
 int /*<<< orphan*/  wglDeleteContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wglMakeCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_release_dc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wined3d_caps_gl_ctx_destroy(const struct wined3d_caps_gl_ctx *ctx)
{
    const struct wined3d_gl_info *gl_info = ctx->gl_info;

    TRACE("Destroying caps GL context.\n");

    /* Both glDeleteProgram and glDeleteBuffers silently ignore 0 IDs but
     * this function might be called before the relevant function pointers
     * in gl_info are initialized. */
    if (ctx->test_program_id || ctx->test_vbo)
    {
        GL_EXTCALL(glDeleteProgram(ctx->test_program_id));
        GL_EXTCALL(glDeleteBuffers(1, &ctx->test_vbo));
    }

    if (!wglMakeCurrent(NULL, NULL))
        ERR("Failed to disable caps GL context.\n");

    if (!wglDeleteContext(ctx->gl_ctx))
    {
        DWORD err = GetLastError();
        ERR("wglDeleteContext(%p) failed, last error %#x.\n", ctx->gl_ctx, err);
    }

    wined3d_release_dc(ctx->wnd, ctx->dc);
    DestroyWindow(ctx->wnd);

    if (ctx->restore_gl_ctx && !wglMakeCurrent(ctx->restore_dc, ctx->restore_gl_ctx))
        ERR("Failed to restore previous GL context.\n");
}