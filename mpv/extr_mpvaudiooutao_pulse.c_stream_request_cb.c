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
 int /*<<< orphan*/  pa_threaded_mainloop_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct ao*) ; 

__attribute__((used)) static void stream_request_cb(pa_stream *s, size_t length, void *userdata)
{
    struct ao *ao = userdata;
    struct priv *priv = ao->priv;
    wakeup(ao);
    pa_threaded_mainloop_signal(priv->mainloop, 0);
}