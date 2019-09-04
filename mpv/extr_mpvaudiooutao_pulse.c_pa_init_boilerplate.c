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
struct priv {char* cfg_host; int /*<<< orphan*/  mainloop; scalar_t__ context; int /*<<< orphan*/  wakeup; int /*<<< orphan*/  wakeup_lock; } ;
struct ao {scalar_t__ probing; int /*<<< orphan*/  client_name; struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENERIC_ERR_MSG (char*) ; 
 int /*<<< orphan*/  MP_ERR (struct ao*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*,long) ; 
 int /*<<< orphan*/  PA_CONTEXT_IS_GOOD (int) ; 
 int PA_CONTEXT_READY ; 
 scalar_t__ PA_ERR_CONNECTIONREFUSED ; 
 int /*<<< orphan*/  context_state_cb ; 
 scalar_t__ pa_context_connect (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pa_context_errno (scalar_t__) ; 
 scalar_t__ pa_context_get_protocol_version (scalar_t__) ; 
 scalar_t__ pa_context_get_server_protocol_version (scalar_t__) ; 
 int pa_context_get_state (scalar_t__) ; 
 scalar_t__ pa_context_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_context_set_state_callback (scalar_t__,int /*<<< orphan*/ ,struct ao*) ; 
 int /*<<< orphan*/  pa_context_set_subscribe_callback (scalar_t__,int /*<<< orphan*/ ,struct ao*) ; 
 long pa_get_library_version () ; 
 int /*<<< orphan*/  pa_threaded_mainloop_get_api (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_new () ; 
 scalar_t__ pa_threaded_mainloop_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  subscribe_cb ; 
 int /*<<< orphan*/  uninit (struct ao*) ; 

__attribute__((used)) static int pa_init_boilerplate(struct ao *ao)
{
    struct priv *priv = ao->priv;
    char *host = priv->cfg_host && priv->cfg_host[0] ? priv->cfg_host : NULL;
    bool locked = false;

    pthread_mutex_init(&priv->wakeup_lock, NULL);
    pthread_cond_init(&priv->wakeup, NULL);

    if (!(priv->mainloop = pa_threaded_mainloop_new())) {
        MP_ERR(ao, "Failed to allocate main loop\n");
        goto fail;
    }

    if (pa_threaded_mainloop_start(priv->mainloop) < 0)
        goto fail;

    pa_threaded_mainloop_lock(priv->mainloop);
    locked = true;

    if (!(priv->context = pa_context_new(pa_threaded_mainloop_get_api(
                                         priv->mainloop), ao->client_name)))
    {
        MP_ERR(ao, "Failed to allocate context\n");
        goto fail;
    }

    MP_VERBOSE(ao, "Library version: %s\n", pa_get_library_version());
    MP_VERBOSE(ao, "Proto: %lu\n",
        (long)pa_context_get_protocol_version(priv->context));
    MP_VERBOSE(ao, "Server proto: %lu\n",
        (long)pa_context_get_server_protocol_version(priv->context));

    pa_context_set_state_callback(priv->context, context_state_cb, ao);
    pa_context_set_subscribe_callback(priv->context, subscribe_cb, ao);

    if (pa_context_connect(priv->context, host, 0, NULL) < 0)
        goto fail;

    /* Wait until the context is ready */
    while (1) {
        int state = pa_context_get_state(priv->context);
        if (state == PA_CONTEXT_READY)
            break;
        if (!PA_CONTEXT_IS_GOOD(state))
            goto fail;
        pa_threaded_mainloop_wait(priv->mainloop);
    }

    pa_threaded_mainloop_unlock(priv->mainloop);
    return 0;

fail:
    if (locked)
        pa_threaded_mainloop_unlock(priv->mainloop);

    if (priv->context) {
        pa_threaded_mainloop_lock(priv->mainloop);
        if (!(pa_context_errno(priv->context) == PA_ERR_CONNECTIONREFUSED
              && ao->probing))
            GENERIC_ERR_MSG("Init failed");
        pa_threaded_mainloop_unlock(priv->mainloop);
    }
    uninit(ao);
    return -1;
}