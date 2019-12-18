#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vo {int /*<<< orphan*/  log; TYPE_2__* x11; } ;
struct TYPE_3__ {scalar_t__ debug; } ;
struct ra_ctx {TYPE_1__ opts; struct vo* vo; struct priv* priv; } ;
struct priv {void* XGetSyncValues; scalar_t__ context; int /*<<< orphan*/  fbc; } ;
typedef  scalar_t__ (* glXCreateContextAttribsARBProc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;
struct TYPE_4__ {int /*<<< orphan*/  display; int /*<<< orphan*/  window; int /*<<< orphan*/  screen; } ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  scalar_t__ GLXContext ;
typedef  int /*<<< orphan*/  GL ;

/* Variables and functions */
 int GLX_CONTEXT_CORE_PROFILE_BIT_ARB ; 
 int GLX_CONTEXT_DEBUG_BIT_ARB ; 
 int GLX_CONTEXT_ES2_PROFILE_BIT_EXT ; 
 int GLX_CONTEXT_FLAGS_ARB ; 
 int GLX_CONTEXT_MAJOR_VERSION_ARB ; 
 int GLX_CONTEXT_MINOR_VERSION_ARB ; 
 int GLX_CONTEXT_PROFILE_MASK_ARB ; 
 int MPGL_VER_GET_MAJOR (int) ; 
 int MPGL_VER_GET_MINOR (int) ; 
 int /*<<< orphan*/  MP_FATAL (struct vo*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct vo*,char*) ; 
 int None ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  glXDestroyContext (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ glXGetProcAddressARB (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  glXMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 char* glXQueryExtensionsString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gl_check_extension (char const*,char*) ; 
 int /*<<< orphan*/  mpgl_load_functions (int /*<<< orphan*/ *,void*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_gl_ctx_test_version (struct ra_ctx*,int,int) ; 
 scalar_t__ strstr (char const*,char*) ; 
 int /*<<< orphan*/  vo_x11_silence_xlib (int) ; 

__attribute__((used)) static bool create_context_x11_gl3(struct ra_ctx *ctx, GL *gl, int gl_version,
                                   bool es)
{
    struct priv *p = ctx->priv;
    struct vo *vo = ctx->vo;

    if (p->context)
        return true;

    if (!ra_gl_ctx_test_version(ctx, gl_version, es))
        return false;

    glXCreateContextAttribsARBProc glXCreateContextAttribsARB =
        (glXCreateContextAttribsARBProc)
            glXGetProcAddressARB((const GLubyte *)"glXCreateContextAttribsARB");

    const char *glxstr =
        glXQueryExtensionsString(vo->x11->display, vo->x11->screen);
    bool have_ctx_ext = glxstr && !!strstr(glxstr, "GLX_ARB_create_context");

    if (!(have_ctx_ext && glXCreateContextAttribsARB)) {
        return false;
    }

    int ctx_flags = ctx->opts.debug ? GLX_CONTEXT_DEBUG_BIT_ARB : 0;
    int profile_mask = GLX_CONTEXT_CORE_PROFILE_BIT_ARB;

    if (es) {
        profile_mask = GLX_CONTEXT_ES2_PROFILE_BIT_EXT;
        if (!(glxstr && strstr(glxstr, "GLX_EXT_create_context_es2_profile")))
            return false;
    }

    int context_attribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, MPGL_VER_GET_MAJOR(gl_version),
        GLX_CONTEXT_MINOR_VERSION_ARB, MPGL_VER_GET_MINOR(gl_version),
        GLX_CONTEXT_PROFILE_MASK_ARB, profile_mask,
        GLX_CONTEXT_FLAGS_ARB, ctx_flags,
        None
    };
    vo_x11_silence_xlib(1);
    GLXContext context = glXCreateContextAttribsARB(vo->x11->display,
                                                    p->fbc, 0, True,
                                                    context_attribs);
    vo_x11_silence_xlib(-1);
    if (!context)
        return false;

    // set context
    if (!glXMakeCurrent(vo->x11->display, vo->x11->window, context)) {
        MP_FATAL(vo, "Could not set GLX context!\n");
        glXDestroyContext(vo->x11->display, context);
        return false;
    }

    p->context = context;

    mpgl_load_functions(gl, (void *)glXGetProcAddressARB, glxstr, vo->log);

    if (gl_check_extension(glxstr, "GLX_OML_sync_control")) {
        p->XGetSyncValues =
            (void *)glXGetProcAddressARB((const GLubyte *)"glXGetSyncValuesOML");
    }
    if (p->XGetSyncValues)
        MP_VERBOSE(vo, "Using GLX_OML_sync_control.\n");

    return true;
}