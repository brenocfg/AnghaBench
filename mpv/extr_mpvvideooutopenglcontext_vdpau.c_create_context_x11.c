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
struct priv {int /*<<< orphan*/  gl; scalar_t__ context; } ;
typedef  scalar_t__ (* glXCreateContextAttribsARBProc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ;
struct TYPE_4__ {int /*<<< orphan*/  display; int /*<<< orphan*/  screen; } ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int /*<<< orphan*/ * GLXFBConfig ;
typedef  scalar_t__ GLXContext ;

/* Variables and functions */
 int GLX_BLUE_SIZE ; 
 int GLX_CONTEXT_CORE_PROFILE_BIT_ARB ; 
 int GLX_CONTEXT_DEBUG_BIT_ARB ; 
 int GLX_CONTEXT_FLAGS_ARB ; 
 int GLX_CONTEXT_MAJOR_VERSION_ARB ; 
 int GLX_CONTEXT_MINOR_VERSION_ARB ; 
 int GLX_CONTEXT_PROFILE_MASK_ARB ; 
 int GLX_DOUBLEBUFFER ; 
 int GLX_GREEN_SIZE ; 
 int GLX_RED_SIZE ; 
 int GLX_TRUE_COLOR ; 
 int GLX_X_RENDERABLE ; 
 int GLX_X_VISUAL_TYPE ; 
 int /*<<< orphan*/  MPGL_VER (int,int) ; 
 int /*<<< orphan*/  MP_ERR (struct vo*,char*) ; 
 int /*<<< orphan*/  MP_FATAL (struct vo*,char*) ; 
 int None ; 
 int True ; 
 int /*<<< orphan*/  XFree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** glXChooseFBConfig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  glXDestroyContext (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  glXGetProcAddressARB (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  glXMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 char* glXQueryExtensionsString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glXQueryVersion (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  mpgl_load_functions (int /*<<< orphan*/ *,void*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_gl_ctx_test_version (struct ra_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 

__attribute__((used)) static bool create_context_x11(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    struct vo *vo = ctx->vo;

    int glx_major, glx_minor;
    if (!glXQueryVersion(vo->x11->display, &glx_major, &glx_minor)) {
        MP_ERR(vo, "GLX not found.\n");
        return false;
    }

    if (!ra_gl_ctx_test_version(ctx, MPGL_VER(glx_major, glx_minor), false))
        return false;

    int glx_attribs[] = {
        GLX_X_RENDERABLE, True,
        GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
        GLX_RED_SIZE, 1,
        GLX_GREEN_SIZE, 1,
        GLX_BLUE_SIZE, 1,
        GLX_DOUBLEBUFFER, True,
        None
    };
    int fbcount;
    GLXFBConfig *fbcs = glXChooseFBConfig(vo->x11->display, vo->x11->screen,
                                          glx_attribs, &fbcount);
    if (!fbcs)
        return false;
    // The list in fbc is sorted (so that the first element is the best).
    GLXFBConfig fbc = fbcount > 0 ? fbcs[0] : NULL;
    XFree(fbcs);
    if (!fbc) {
        MP_ERR(vo, "no GLX support present\n");
        return false;
    }

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
    int context_attribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 0,
        GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
        GLX_CONTEXT_FLAGS_ARB, ctx_flags,
        None
    };
    GLXContext context = glXCreateContextAttribsARB(vo->x11->display, fbc, 0,
                                                    True, context_attribs);
    if (!context)
        return false;

    // Pass 0 as drawable for offscreen use. This is probably (?) not valid in
    // standard GLX, but the nVidia drivers accept it.
    if (!glXMakeCurrent(vo->x11->display, 0, context)) {
        MP_FATAL(vo, "Could not set GLX context!\n");
        glXDestroyContext(vo->x11->display, context);
        return false;
    }

    p->context = context;
    mpgl_load_functions(&p->gl, (void *)glXGetProcAddressARB, glxstr, vo->log);
    return true;
}