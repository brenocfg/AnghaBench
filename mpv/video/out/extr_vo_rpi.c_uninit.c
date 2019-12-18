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
struct vo {struct priv* priv; } ;
struct priv {int /*<<< orphan*/  display_mutex; int /*<<< orphan*/  display_cond; scalar_t__ renderer; scalar_t__ update; int /*<<< orphan*/  next_image; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_dispmanx (struct vo*) ; 
 int /*<<< orphan*/  mmal_component_release (scalar_t__) ; 
 int /*<<< orphan*/  mmal_vc_deinit () ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tv_callback ; 
 int /*<<< orphan*/  vc_dispmanx_update_submit_sync (scalar_t__) ; 
 int /*<<< orphan*/  vc_tv_unregister_callback_full (int /*<<< orphan*/ ,struct vo*) ; 

__attribute__((used)) static void uninit(struct vo *vo)
{
    struct priv *p = vo->priv;

    vc_tv_unregister_callback_full(tv_callback, vo);

    talloc_free(p->next_image);

    destroy_dispmanx(vo);

    if (p->update)
        vc_dispmanx_update_submit_sync(p->update);

    if (p->renderer)
        mmal_component_release(p->renderer);

    mmal_vc_deinit();

    pthread_cond_destroy(&p->display_cond);
    pthread_mutex_destroy(&p->display_mutex);
}