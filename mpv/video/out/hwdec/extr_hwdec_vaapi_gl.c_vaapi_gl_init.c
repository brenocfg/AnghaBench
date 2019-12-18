#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ra_hwdec {int /*<<< orphan*/  ra; struct priv_owner* priv; } ;
struct priv_owner {int /*<<< orphan*/  interop_unmap; int /*<<< orphan*/  interop_map_legacy; int /*<<< orphan*/  interop_map; int /*<<< orphan*/  interop_uninit; int /*<<< orphan*/  interop_init; } ;
struct TYPE_3__ {char const* extensions; int mpgl_caps; } ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_EXTENSIONS ; 
 int MPGL_CAP_TEX_RG ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ra_hwdec const*,char*) ; 
 int /*<<< orphan*/  eglGetCurrentContext () ; 
 int /*<<< orphan*/  eglGetCurrentDisplay () ; 
 char* eglQueryString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ra_gl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_is_gl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 
 int /*<<< orphan*/  vaapi_gl_map ; 
 int /*<<< orphan*/  vaapi_gl_map_legacy ; 
 int /*<<< orphan*/  vaapi_gl_mapper_init ; 
 int /*<<< orphan*/  vaapi_gl_mapper_uninit ; 
 int /*<<< orphan*/  vaapi_gl_unmap ; 

bool vaapi_gl_init(const struct ra_hwdec *hw)
{
    struct priv_owner *p = hw->priv;
    if (!ra_is_gl(hw->ra)) {
        // This is not an OpenGL RA.
        return false;
    }

    if (!eglGetCurrentContext())
        return false;

    const char *exts = eglQueryString(eglGetCurrentDisplay(), EGL_EXTENSIONS);
    if (!exts)
        return false;

    GL *gl = ra_gl_get(hw->ra);
    if (!strstr(exts, "EXT_image_dma_buf_import") ||
        !strstr(exts, "EGL_KHR_image_base") ||
        !strstr(gl->extensions, "GL_OES_EGL_image") ||
        !(gl->mpgl_caps & MPGL_CAP_TEX_RG))
        return false;

    MP_VERBOSE(hw, "using VAAPI EGL interop\n");

    p->interop_init = vaapi_gl_mapper_init;
    p->interop_uninit = vaapi_gl_mapper_uninit;
    p->interop_map = vaapi_gl_map;
    p->interop_map_legacy = vaapi_gl_map_legacy;
    p->interop_unmap = vaapi_gl_unmap;

    return true;
}