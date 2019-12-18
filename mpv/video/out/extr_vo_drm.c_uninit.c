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
struct priv {scalar_t__ fb_queue_len; unsigned int buf_count; int /*<<< orphan*/  cur_frame_cropped; int /*<<< orphan*/  cur_frame; int /*<<< orphan*/  last_input; int /*<<< orphan*/  vt_switcher; scalar_t__ vt_switcher_active; TYPE_1__* kms; int /*<<< orphan*/ * bufs; } ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  crtc_release (struct vo*) ; 
 int /*<<< orphan*/  fb_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kms_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  swapchain_step (struct vo*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt_switcher_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uninit(struct vo *vo)
{
    struct priv *p = vo->priv;

    crtc_release(vo);

    while (p->fb_queue_len > 0) {
        swapchain_step(vo);
    }

    if (p->kms) {
        for (unsigned int i = 0; i < p->buf_count; i++)
            fb_destroy(p->kms->fd, &p->bufs[i]);
        kms_destroy(p->kms);
        p->kms = NULL;
    }

    if (p->vt_switcher_active)
        vt_switcher_destroy(&p->vt_switcher);

    talloc_free(p->last_input);
    talloc_free(p->cur_frame);
    talloc_free(p->cur_frame_cropped);
}