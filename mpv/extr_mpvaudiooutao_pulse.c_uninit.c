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
struct priv {int /*<<< orphan*/  wakeup_lock; int /*<<< orphan*/  wakeup; int /*<<< orphan*/ * mainloop; int /*<<< orphan*/ * context; int /*<<< orphan*/ * stream; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  pa_context_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_context_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uninit(struct ao *ao)
{
    struct priv *priv = ao->priv;

    if (priv->mainloop)
        pa_threaded_mainloop_stop(priv->mainloop);

    if (priv->stream) {
        pa_stream_disconnect(priv->stream);
        pa_stream_unref(priv->stream);
        priv->stream = NULL;
    }

    if (priv->context) {
        pa_context_disconnect(priv->context);
        pa_context_unref(priv->context);
        priv->context = NULL;
    }

    if (priv->mainloop) {
        pa_threaded_mainloop_free(priv->mainloop);
        priv->mainloop = NULL;
    }

    pthread_cond_destroy(&priv->wakeup);
    pthread_mutex_destroy(&priv->wakeup_lock);
}