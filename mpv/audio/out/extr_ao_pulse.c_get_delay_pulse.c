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
struct priv {int /*<<< orphan*/  mainloop; int /*<<< orphan*/  context; int /*<<< orphan*/  stream; } ;
struct ao {struct priv* priv; } ;
typedef  double pa_usec_t ;

/* Variables and functions */
 int /*<<< orphan*/  GENERIC_ERR_MSG (char*) ; 
 scalar_t__ PA_ERR_NODATA ; 
 scalar_t__ pa_context_errno (int /*<<< orphan*/ ) ; 
 scalar_t__ pa_stream_get_latency (int /*<<< orphan*/ ,double*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_wait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static double get_delay_pulse(struct ao *ao)
{
    struct priv *priv = ao->priv;
    pa_usec_t latency = (pa_usec_t) -1;
    pa_threaded_mainloop_lock(priv->mainloop);
    while (pa_stream_get_latency(priv->stream, &latency, NULL) < 0) {
        if (pa_context_errno(priv->context) != PA_ERR_NODATA) {
            GENERIC_ERR_MSG("pa_stream_get_latency() failed");
            break;
        }
        /* Wait until latency data is available again */
        pa_threaded_mainloop_wait(priv->mainloop);
    }
    pa_threaded_mainloop_unlock(priv->mainloop);
    return latency == (pa_usec_t) -1 ? 0 : latency / 1000000.0;
}