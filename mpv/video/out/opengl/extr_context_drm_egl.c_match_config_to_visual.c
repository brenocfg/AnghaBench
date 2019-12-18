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
struct ra_ctx {struct priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  display; } ;
struct priv {scalar_t__ const gbm_format; TYPE_1__ egl; } ;
typedef  scalar_t__ const EGLint ;
typedef  int /*<<< orphan*/  EGLConfig ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_NATIVE_VISUAL_ID ; 
 int /*<<< orphan*/  MP_ERR (struct ra_ctx*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ra_ctx*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglGetConfigAttrib (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__ const*) ; 
 int /*<<< orphan*/  fallback_format_for (scalar_t__ const) ; 
 int /*<<< orphan*/  gbm_format_to_string (scalar_t__ const) ; 

__attribute__((used)) static int match_config_to_visual(void *user_data, EGLConfig *configs, int num_configs)
{
    struct ra_ctx *ctx = (struct ra_ctx*)user_data;
    struct priv *p = ctx->priv;
    const EGLint visual_id[] = {
        (EGLint)p->gbm_format,
        (EGLint)fallback_format_for(p->gbm_format),
        0
    };

    for (unsigned int i = 0; visual_id[i] != 0; ++i) {
        MP_VERBOSE(ctx, "Attempting to find EGLConfig matching %s\n",
                   gbm_format_to_string(visual_id[i]));
        for (unsigned int j = 0; j < num_configs; ++j) {
            EGLint id;

            if (!eglGetConfigAttrib(p->egl.display, configs[j], EGL_NATIVE_VISUAL_ID, &id))
                continue;

            if (visual_id[i] == id) {
                MP_VERBOSE(ctx, "Found matching EGLConfig for %s\n",
                           gbm_format_to_string(visual_id[i]));
                return j;
            }
        }
        MP_VERBOSE(ctx, "No matching EGLConfig for %s\n", gbm_format_to_string(visual_id[i]));
    }

    MP_ERR(ctx, "Could not find EGLConfig matching the GBM visual (%s).\n",
           gbm_format_to_string(p->gbm_format));
    return -1;
}