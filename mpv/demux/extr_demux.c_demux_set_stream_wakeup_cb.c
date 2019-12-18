#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sh_stream {TYPE_2__* ds; } ;
struct TYPE_4__ {void (* wakeup_cb ) (void*) ;int need_wakeup; TYPE_1__* in; void* wakeup_cb_ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void demux_set_stream_wakeup_cb(struct sh_stream *sh,
                                void (*cb)(void *ctx), void *ctx)
{
    pthread_mutex_lock(&sh->ds->in->lock);
    sh->ds->wakeup_cb = cb;
    sh->ds->wakeup_cb_ctx = ctx;
    sh->ds->need_wakeup = true;
    pthread_mutex_unlock(&sh->ds->in->lock);
}