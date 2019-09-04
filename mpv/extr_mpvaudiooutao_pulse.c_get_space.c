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
struct ao {size_t sstride; struct priv* priv; } ;

/* Variables and functions */
 size_t pa_stream_writable_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_space(struct ao *ao)
{
    struct priv *priv = ao->priv;
    pa_threaded_mainloop_lock(priv->mainloop);
    size_t space = pa_stream_writable_size(priv->stream);
    pa_threaded_mainloop_unlock(priv->mainloop);
    return space / ao->sstride;
}