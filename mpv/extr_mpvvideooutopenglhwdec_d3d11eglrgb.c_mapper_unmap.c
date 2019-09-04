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
struct ra_hwdec_mapper {int /*<<< orphan*/ * tex; int /*<<< orphan*/  ra; struct priv* priv; TYPE_1__* owner; } ;
struct priv_owner {int /*<<< orphan*/  egl_display; } ;
struct priv {int /*<<< orphan*/ * egl_surface; } ;
struct TYPE_2__ {struct priv_owner* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_BACK_BUFFER ; 
 int /*<<< orphan*/  eglDestroySurface (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglReleaseTexImage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_tex_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mapper_unmap(struct ra_hwdec_mapper *mapper)
{
    struct priv_owner *o = mapper->owner->priv;
    struct priv *p = mapper->priv;
    ra_tex_free(mapper->ra, &mapper->tex[0]);
    if (p->egl_surface) {
        eglReleaseTexImage(o->egl_display, p->egl_surface, EGL_BACK_BUFFER);
        eglDestroySurface(o->egl_display, p->egl_surface);
    }
    p->egl_surface = NULL;
}