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
struct vo {struct priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  ra; } ;
struct priv {scalar_t__ osd_overlay; int /*<<< orphan*/  update; TYPE_1__ egl; int /*<<< orphan*/ * gl_video; scalar_t__ window; } ;

/* Variables and functions */
 int /*<<< orphan*/  gl_video_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_egl_rpi_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  ra_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_dispmanx_element_remove (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void destroy_overlays(struct vo *vo)
{
    struct priv *p = vo->priv;

    if (p->window)
        vc_dispmanx_element_remove(p->update, p->window);
    p->window = 0;

    gl_video_uninit(p->gl_video);
    p->gl_video = NULL;
    ra_free(&p->egl.ra);
    mp_egl_rpi_destroy(&p->egl);

    if (p->osd_overlay)
        vc_dispmanx_element_remove(p->update, p->osd_overlay);
    p->osd_overlay = 0;
}