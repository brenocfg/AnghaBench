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
struct ra_hwdec_mapper {int /*<<< orphan*/ * tex; int /*<<< orphan*/  ra; struct priv* priv; } ;
struct priv {scalar_t__ query9; scalar_t__ texture9; scalar_t__ surface9; scalar_t__ egl_surface; scalar_t__ egl_display; int /*<<< orphan*/  gl_texture; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* DeleteTextures ) (int,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_BACK_BUFFER ; 
 int /*<<< orphan*/  IDirect3DQuery9_Release (scalar_t__) ; 
 int /*<<< orphan*/  IDirect3DSurface9_Release (scalar_t__) ; 
 int /*<<< orphan*/  IDirect3DTexture9_Release (scalar_t__) ; 
 int /*<<< orphan*/  eglDestroySurface (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  eglReleaseTexImage (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* ra_gl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_tex_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mapper_uninit(struct ra_hwdec_mapper *mapper)
{
    struct priv *p = mapper->priv;
    GL *gl = ra_gl_get(mapper->ra);

    ra_tex_free(mapper->ra, &mapper->tex[0]);
    gl->DeleteTextures(1, &p->gl_texture);

    if (p->egl_display && p->egl_surface) {
        eglReleaseTexImage(p->egl_display, p->egl_surface, EGL_BACK_BUFFER);
        eglDestroySurface(p->egl_display, p->egl_surface);
    }

    if (p->surface9)
        IDirect3DSurface9_Release(p->surface9);

    if (p->texture9)
        IDirect3DTexture9_Release(p->texture9);

    if (p->query9)
        IDirect3DQuery9_Release(p->query9);
}