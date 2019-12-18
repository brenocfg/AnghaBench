#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vo {int /*<<< orphan*/  log; TYPE_1__* x11; } ;
struct ra_ctx {struct vo* vo; struct priv* priv; } ;
struct priv {scalar_t__ context; int /*<<< orphan*/  vinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  screen; int /*<<< orphan*/  window; int /*<<< orphan*/ * display; } ;
typedef  scalar_t__ GLXContext ;
typedef  int /*<<< orphan*/  GL ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FATAL (struct vo*,char*) ; 
 int /*<<< orphan*/  True ; 
 scalar_t__ glXCreateContext (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glXDestroyContext (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ glXGetProcAddressARB ; 
 int /*<<< orphan*/  glXMakeCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 char* glXQueryExtensionsString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpgl_load_functions (int /*<<< orphan*/ *,void*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool create_context_x11_old(struct ra_ctx *ctx, GL *gl)
{
    struct priv *p = ctx->priv;
    Display *display = ctx->vo->x11->display;
    struct vo *vo = ctx->vo;

    if (p->context)
        return true;

    if (!p->vinfo) {
        MP_FATAL(vo, "Can't create a legacy GLX context without X visual\n");
        return false;
    }

    GLXContext new_context = glXCreateContext(display, p->vinfo, NULL, True);
    if (!new_context) {
        MP_FATAL(vo, "Could not create GLX context!\n");
        return false;
    }

    if (!glXMakeCurrent(display, ctx->vo->x11->window, new_context)) {
        MP_FATAL(vo, "Could not set GLX context!\n");
        glXDestroyContext(display, new_context);
        return false;
    }

    const char *glxstr = glXQueryExtensionsString(display, ctx->vo->x11->screen);

    mpgl_load_functions(gl, (void *)glXGetProcAddressARB, glxstr, vo->log);

    p->context = new_context;

    return true;
}