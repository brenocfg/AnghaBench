#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vo {struct priv* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  egl_surface; int /*<<< orphan*/  egl_display; scalar_t__ gl; } ;
struct priv {int skip_osd; scalar_t__ display_synced; TYPE_2__* renderer; TYPE_1__ egl; struct mp_image* next_image; int /*<<< orphan*/  renderer_enabled; } ;
struct mp_image {scalar_t__* planes; } ;
struct TYPE_7__ {struct mp_image* user_data; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** input; } ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct vo*,char*) ; 
 int /*<<< orphan*/  eglSwapBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_send_buffer (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 
 int /*<<< orphan*/  wait_next_vsync (struct vo*) ; 

__attribute__((used)) static void flip_page(struct vo *vo)
{
    struct priv *p = vo->priv;

    if (!p->renderer_enabled)
        return;

    struct mp_image *mpi = p->next_image;
    p->next_image = NULL;

    // For OSD
    if (!p->skip_osd && p->egl.gl)
        eglSwapBuffers(p->egl.egl_display, p->egl.egl_surface);
    p->skip_osd = false;

    if (mpi) {
        MMAL_PORT_T *input = p->renderer->input[0];
        MMAL_BUFFER_HEADER_T *ref = (void *)mpi->planes[3];

        // Assume this field is free for use by us.
        ref->user_data = mpi;

        if (mmal_port_send_buffer(input, ref)) {
            MP_ERR(vo, "could not queue picture!\n");
            talloc_free(mpi);
        }
    }

    if (p->display_synced)
        wait_next_vsync(vo);
}