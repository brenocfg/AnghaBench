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
struct ra_ctx {int /*<<< orphan*/  vo; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  ctx; int /*<<< orphan*/  pix; TYPE_1__* opts; } ;
struct TYPE_2__ {scalar_t__ cocoa_force_dedicated_gpu; } ;
typedef  int /*<<< orphan*/  GLint ;
typedef  scalar_t__ CGLPixelFormatAttribute ;
typedef  int /*<<< orphan*/  CGLOpenGLProfile ;
typedef  scalar_t__ CGLError ;

/* Variables and functions */
 scalar_t__ CGLChoosePixelFormat (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CGLCreateContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CGLErrorString (scalar_t__) ; 
 int MP_ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  MP_ERR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ kCGLBadAttribute ; 
 scalar_t__ kCGLNoError ; 
 scalar_t__ kCGLPFAAccelerated ; 
 scalar_t__ kCGLPFAAllowOfflineRenderers ; 
 scalar_t__ kCGLPFAOpenGLProfile ; 
 scalar_t__ kCGLPFASupportsAutomaticGraphicsSwitching ; 

__attribute__((used)) static CGLError test_gl_version(struct ra_ctx *ctx, CGLOpenGLProfile ver)
{
    struct priv *p = ctx->priv;

    CGLPixelFormatAttribute attrs[] = {
        // let this array ordered by the inverse order of the most probably
        // rejected attribute to preserve the fallback code
        kCGLPFAOpenGLProfile,
        (CGLPixelFormatAttribute) ver,
        kCGLPFAAccelerated,
        kCGLPFAAllowOfflineRenderers,
        // keep this one last to apply the cocoa-force-dedicated-gpu option
        kCGLPFASupportsAutomaticGraphicsSwitching,
        0
    };

    GLint npix;
    CGLError err;
    int supported_attribute = MP_ARRAY_SIZE(attrs)-1;

    if (p->opts->cocoa_force_dedicated_gpu)
        attrs[--supported_attribute] = 0;

    err = CGLChoosePixelFormat(attrs, &p->pix, &npix);
    while (err == kCGLBadAttribute && supported_attribute > 3) {
        // kCGLPFASupportsAutomaticGraphicsSwitching is probably not
        // supported by the current hardware. Falling back to not using
        // it and disallowing Offline Renderers if further restrictions
        // apply
        attrs[--supported_attribute] = 0;
        err = CGLChoosePixelFormat(attrs, &p->pix, &npix);
    }

    if (err != kCGLNoError) {
        MP_ERR(ctx->vo, "error creating CGL pixel format: %s (%d)\n",
               CGLErrorString(err), err);
        goto error_out;
    }

    err = CGLCreateContext(p->pix, 0, &p->ctx);

error_out:
    return err;
}