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
struct priv {int /*<<< orphan*/  context; int /*<<< orphan*/  mainloop; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  PA_SUBSCRIPTION_MASK_SINK ; 
 int /*<<< orphan*/  context_success_cb ; 
 int /*<<< orphan*/  pa_context_subscribe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ao*) ; 
 scalar_t__ pa_init_boilerplate (struct ao*) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitop (struct priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hotplug_init(struct ao *ao)
{
    struct priv *priv = ao->priv;
    if (pa_init_boilerplate(ao) < 0)
        return -1;

    pa_threaded_mainloop_lock(priv->mainloop);
    waitop(priv, pa_context_subscribe(priv->context, PA_SUBSCRIPTION_MASK_SINK,
                                      context_success_cb, ao));

    return 0;
}