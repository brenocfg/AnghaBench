#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct ra_ctx {int /*<<< orphan*/  vo; struct priv* priv; } ;
struct priv {scalar_t__ gbm_format; TYPE_3__* kms; } ;
struct TYPE_10__ {unsigned int count_formats; scalar_t__* formats; } ;
typedef  TYPE_4__ drmModePlane ;
struct TYPE_9__ {TYPE_2__* atomic_context; int /*<<< orphan*/  fd; } ;
struct TYPE_8__ {TYPE_1__* draw_plane; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  drmModeFreePlane (TYPE_4__*) ; 
 TYPE_4__* drmModeGetPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gbm_format_to_string (scalar_t__) ; 

__attribute__((used)) static bool probe_gbm_format(struct ra_ctx *ctx, uint32_t argb_format, uint32_t xrgb_format)
{
    struct priv *p = ctx->priv;

    if (!p->kms->atomic_context) {
        p->gbm_format = xrgb_format;
        MP_VERBOSE(ctx->vo, "Not using DRM Atomic: Use %s for draw plane.\n",
                   gbm_format_to_string(xrgb_format));
        return true;
    }

    drmModePlane *drmplane =
        drmModeGetPlane(p->kms->fd, p->kms->atomic_context->draw_plane->id);
    bool have_argb = false;
    bool have_xrgb = false;
    bool result = false;
    for (unsigned int i = 0; i < drmplane->count_formats; ++i) {
        if (drmplane->formats[i] == argb_format) {
            have_argb = true;
        } else if (drmplane->formats[i] == xrgb_format) {
            have_xrgb = true;
        }
    }

    if (have_argb) {
        p->gbm_format = argb_format;
        MP_VERBOSE(ctx->vo, "%s supported by draw plane.\n", gbm_format_to_string(argb_format));
        result = true;
    } else if (have_xrgb) {
        p->gbm_format = xrgb_format;
        MP_VERBOSE(ctx->vo, "%s not supported by draw plane: Falling back to %s.\n",
                   gbm_format_to_string(argb_format), gbm_format_to_string(xrgb_format));
        result = true;
    }

    drmModeFreePlane(drmplane);
    return result;
}