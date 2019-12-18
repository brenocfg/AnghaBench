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
struct ra_ctx {TYPE_2__* vo; int /*<<< orphan*/  global; struct priv* priv; } ;
struct priv {int opt_swapinterval; int current_swapinterval; int /*<<< orphan*/  (* real_wglSwapInterval ) (int) ;int /*<<< orphan*/  hdc; } ;
struct TYPE_4__ {TYPE_1__* opts; } ;
struct TYPE_3__ {int /*<<< orphan*/  fullscreen; } ;

/* Variables and functions */
 scalar_t__ DwmFlush () ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_2__*,char*,int) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SwapBuffers (int /*<<< orphan*/ ) ; 
 scalar_t__ compositor_active (struct ra_ctx*) ; 
 int /*<<< orphan*/  m_option_type_choice ; 
 int /*<<< orphan*/  mp_read_option_raw (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static void wgl_swap_buffers(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    SwapBuffers(p->hdc);

    // default if we don't DwmFLush
    int new_swapinterval = p->opt_swapinterval;

    int dwm_flush_opt;
    mp_read_option_raw(ctx->global, "opengl-dwmflush", &m_option_type_choice,
                       &dwm_flush_opt);

    if (dwm_flush_opt >= 0) {
        if ((dwm_flush_opt == 1 && !ctx->vo->opts->fullscreen) ||
            (dwm_flush_opt == 2) ||
            (dwm_flush_opt == 0 && compositor_active(ctx)))
        {
            if (DwmFlush() == S_OK)
                new_swapinterval = 0;
        }
    }

    if (new_swapinterval != p->current_swapinterval &&
        p->real_wglSwapInterval)
    {
        p->real_wglSwapInterval(new_swapinterval);
        MP_VERBOSE(ctx->vo, "set SwapInterval(%d)\n", new_swapinterval);
    }
    p->current_swapinterval = new_swapinterval;
}