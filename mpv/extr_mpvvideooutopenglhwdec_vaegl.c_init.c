#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ra_hwdec {int /*<<< orphan*/  devs; TYPE_1__* driver; scalar_t__ probing; int /*<<< orphan*/  log; int /*<<< orphan*/  ra; struct priv_owner* priv; } ;
struct priv_owner {TYPE_3__* ctx; int /*<<< orphan*/ * formats; int /*<<< orphan*/  display; } ;
struct TYPE_10__ {int /*<<< orphan*/  driver_name; int /*<<< orphan*/ * supported_formats; } ;
struct TYPE_9__ {TYPE_6__ hwctx; int /*<<< orphan*/  av_device_ref; } ;
struct TYPE_8__ {char const* extensions; int mpgl_caps; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_EXTENSIONS ; 
 int MPGL_CAP_TEX_RG ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ra_hwdec*,char*) ; 
 int /*<<< orphan*/  create_native_va_display (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  determine_working_formats (struct ra_hwdec*) ; 
 int /*<<< orphan*/  eglGetCurrentContext () ; 
 int /*<<< orphan*/  eglGetCurrentDisplay () ; 
 char* eglQueryString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwdec_devices_add (int /*<<< orphan*/ ,TYPE_6__*) ; 
 TYPE_2__* ra_gl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_is_gl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 
 int /*<<< orphan*/  vaTerminate (int /*<<< orphan*/ ) ; 
 scalar_t__ va_guess_if_emulated (TYPE_3__*) ; 
 TYPE_3__* va_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init(struct ra_hwdec *hw)
{
    struct priv_owner *p = hw->priv;

    if (!ra_is_gl(hw->ra) || !eglGetCurrentContext())
        return -1;

    const char *exts = eglQueryString(eglGetCurrentDisplay(), EGL_EXTENSIONS);
    if (!exts)
        return -1;

    GL *gl = ra_gl_get(hw->ra);
    if (!strstr(exts, "EXT_image_dma_buf_import") ||
        !strstr(exts, "EGL_KHR_image_base") ||
        !strstr(gl->extensions, "GL_OES_EGL_image") ||
        !(gl->mpgl_caps & MPGL_CAP_TEX_RG))
        return -1;

    p->display = create_native_va_display(hw->ra, hw->log);
    if (!p->display) {
        MP_VERBOSE(hw, "Could not create a VA display.\n");
        return -1;
    }

    p->ctx = va_initialize(p->display, hw->log, true);
    if (!p->ctx) {
        vaTerminate(p->display);
        return -1;
    }
    if (!p->ctx->av_device_ref) {
        MP_VERBOSE(hw, "libavutil vaapi code rejected the driver?\n");
        return -1;
    }

    if (hw->probing && va_guess_if_emulated(p->ctx)) {
        return -1;
    }

    MP_VERBOSE(hw, "using VAAPI EGL interop\n");

    determine_working_formats(hw);
    if (!p->formats || !p->formats[0]) {
        return -1;
    }

    p->ctx->hwctx.supported_formats = p->formats;
    p->ctx->hwctx.driver_name = hw->driver->name;
    hwdec_devices_add(hw->devs, &p->ctx->hwctx);
    return 0;
}