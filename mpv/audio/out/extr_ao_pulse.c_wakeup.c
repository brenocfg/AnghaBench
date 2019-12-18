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
struct priv {int wakeup_status; int /*<<< orphan*/  wakeup_lock; int /*<<< orphan*/  wakeup; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wakeup(struct ao *ao)
{
    struct priv *priv = ao->priv;
    pthread_mutex_lock(&priv->wakeup_lock);
    priv->wakeup_status = 1;
    pthread_cond_signal(&priv->wakeup);
    pthread_mutex_unlock(&priv->wakeup_lock);
}