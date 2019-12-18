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
struct ao {struct priv* priv; } ;
typedef  int /*<<< orphan*/  pa_stream ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*) ; 
#define  PA_STREAM_FAILED 130 
#define  PA_STREAM_READY 129 
#define  PA_STREAM_TERMINATED 128 
 int /*<<< orphan*/  ao_request_reload (struct ao*) ; 
 int pa_stream_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stream_state_cb(pa_stream *s, void *userdata)
{
    struct ao *ao = userdata;
    struct priv *priv = ao->priv;
    switch (pa_stream_get_state(s)) {
    case PA_STREAM_FAILED:
        MP_VERBOSE(ao, "Stream failed.\n");
        ao_request_reload(ao);
        pa_threaded_mainloop_signal(priv->mainloop, 0);
        break;
    case PA_STREAM_READY:
    case PA_STREAM_TERMINATED:
        pa_threaded_mainloop_signal(priv->mainloop, 0);
        break;
    }
}