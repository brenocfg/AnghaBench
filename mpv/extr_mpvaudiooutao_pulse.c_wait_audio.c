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
struct priv {int /*<<< orphan*/  wakeup_lock; scalar_t__ wakeup_status; int /*<<< orphan*/  wakeup; } ;
struct ao {struct priv* priv; } ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wait_audio(struct ao *ao, pthread_mutex_t *lock)
{
    struct priv *priv = ao->priv;
    // We don't use this mutex, because pulse like to call stream_request_cb
    // while we have the central mutex held.
    pthread_mutex_unlock(lock);
    pthread_mutex_lock(&priv->wakeup_lock);
    while (!priv->wakeup_status)
        pthread_cond_wait(&priv->wakeup, &priv->wakeup_lock);
    priv->wakeup_status = 0;
    pthread_mutex_unlock(&priv->wakeup_lock);
    pthread_mutex_lock(lock);
    return 0;
}