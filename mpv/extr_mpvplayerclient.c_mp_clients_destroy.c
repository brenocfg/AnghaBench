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
struct MPContext {TYPE_1__* clients; } ;
struct TYPE_2__ {scalar_t__ num_clients; int /*<<< orphan*/  lock; scalar_t__ render_context; int /*<<< orphan*/  gl_cb_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FATAL (struct MPContext*,char*) ; 
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (TYPE_1__*) ; 

void mp_clients_destroy(struct MPContext *mpctx)
{
    if (!mpctx->clients)
        return;
    assert(mpctx->clients->num_clients == 0);

    TA_FREEP(&mpctx->clients->gl_cb_ctx);

    // The API user is supposed to call mpv_render_context_free(). It's simply
    // not allowed not to do this.
    if (mpctx->clients->render_context) {
        MP_FATAL(mpctx, "Broken API use: mpv_render_context_free() not called.\n");
        abort();
    }

    pthread_mutex_destroy(&mpctx->clients->lock);
    talloc_free(mpctx->clients);
    mpctx->clients = NULL;
}