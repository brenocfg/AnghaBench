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
struct priv {int num_buffers; scalar_t__ context; scalar_t__ config; int /*<<< orphan*/  av_device_ref; int /*<<< orphan*/  queue; int /*<<< orphan*/  hw_pool; int /*<<< orphan*/  display; int /*<<< orphan*/ * buffers; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
 scalar_t__ VA_INVALID_ID ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_frames (struct mp_filter*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vaDestroyBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vaDestroyConfig (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vaDestroyContext (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void uninit(struct mp_filter *vf)
{
    struct priv *p = vf->priv;
    for (int i = 0; i < p->num_buffers; i++)
        vaDestroyBuffer(p->display, p->buffers[i]);
    if (p->context != VA_INVALID_ID)
        vaDestroyContext(p->display, p->context);
    if (p->config != VA_INVALID_ID)
        vaDestroyConfig(p->display, p->config);
    av_buffer_unref(&p->hw_pool);
    flush_frames(vf);
    talloc_free(p->queue);
    av_buffer_unref(&p->av_device_ref);
}