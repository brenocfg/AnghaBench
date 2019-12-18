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
struct priv {int /*<<< orphan*/  mainloop; } ;
typedef  scalar_t__ pa_operation_state_t ;
typedef  int /*<<< orphan*/  pa_operation ;

/* Variables and functions */
 scalar_t__ PA_OPERATION_DONE ; 
 scalar_t__ PA_OPERATION_RUNNING ; 
 scalar_t__ pa_operation_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_operation_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_wait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int waitop(struct priv *priv, pa_operation *op)
{
    if (!op) {
        pa_threaded_mainloop_unlock(priv->mainloop);
        return 0;
    }
    pa_operation_state_t state = pa_operation_get_state(op);
    while (state == PA_OPERATION_RUNNING) {
        pa_threaded_mainloop_wait(priv->mainloop);
        state = pa_operation_get_state(op);
    }
    pa_operation_unref(op);
    pa_threaded_mainloop_unlock(priv->mainloop);
    return state == PA_OPERATION_DONE;
}