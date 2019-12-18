#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mp_egl_rpi {int /*<<< orphan*/ * gl; scalar_t__ egl_display; scalar_t__ egl_context; scalar_t__ egl_surface; } ;

/* Variables and functions */
 scalar_t__ EGL_NO_CONTEXT ; 
 scalar_t__ EGL_NO_DISPLAY ; 
 int /*<<< orphan*/  EGL_NO_SURFACE ; 
 int /*<<< orphan*/  eglDestroyContext (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  eglDestroySurface (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  eglMakeCurrent (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  eglReleaseThread () ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mp_egl_rpi_destroy(struct mp_egl_rpi *p)
{
    if (p->egl_display) {
        eglMakeCurrent(p->egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE,
                       EGL_NO_CONTEXT);
    }
    if (p->egl_surface)
        eglDestroySurface(p->egl_display, p->egl_surface);
    if (p->egl_context)
        eglDestroyContext(p->egl_display, p->egl_context);
    p->egl_context = EGL_NO_CONTEXT;
    eglReleaseThread();
    p->egl_display = EGL_NO_DISPLAY;
    talloc_free(p->gl);
    p->gl = NULL;
}