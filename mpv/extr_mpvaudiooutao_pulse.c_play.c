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
struct priv {int /*<<< orphan*/  mainloop; int /*<<< orphan*/  stream; } ;
struct ao {int sstride; struct priv* priv; } ;
typedef  int /*<<< orphan*/  pa_operation ;

/* Variables and functions */
 int AOPLAY_FINAL_CHUNK ; 
 int /*<<< orphan*/  GENERIC_ERR_MSG (char*) ; 
 int /*<<< orphan*/  PA_SEEK_RELATIVE ; 
 int /*<<< orphan*/  pa_operation_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pa_stream_trigger (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pa_stream_write (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int play(struct ao *ao, void **data, int samples, int flags)
{
    struct priv *priv = ao->priv;
    pa_threaded_mainloop_lock(priv->mainloop);
    if (pa_stream_write(priv->stream, data[0], samples * ao->sstride, NULL, 0,
                        PA_SEEK_RELATIVE) < 0) {
        GENERIC_ERR_MSG("pa_stream_write() failed");
        samples = -1;
    }
    if (flags & AOPLAY_FINAL_CHUNK) {
        // Force start in case the stream was too short for prebuf
        pa_operation *op = pa_stream_trigger(priv->stream, NULL, NULL);
        pa_operation_unref(op);
    }
    pa_threaded_mainloop_unlock(priv->mainloop);
    return samples;
}