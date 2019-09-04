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
struct priv {int retval; int /*<<< orphan*/  mainloop; } ;
struct ao {struct priv* priv; } ;
typedef  int /*<<< orphan*/  pa_stream ;

/* Variables and functions */
 int /*<<< orphan*/  pa_threaded_mainloop_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void success_cb(pa_stream *s, int success, void *userdata)
{
    struct ao *ao = userdata;
    struct priv *priv = ao->priv;
    priv->retval = success;
    pa_threaded_mainloop_signal(priv->mainloop, 0);
}