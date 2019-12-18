#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dec_sub {int /*<<< orphan*/  lock; struct dec_sub* sd; TYPE_1__* driver; int /*<<< orphan*/  sh; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* uninit ) (struct dec_sub*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  demux_set_stream_wakeup_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dec_sub*) ; 
 int /*<<< orphan*/  sub_reset (struct dec_sub*) ; 
 int /*<<< orphan*/  talloc_free (struct dec_sub*) ; 

void sub_destroy(struct dec_sub *sub)
{
    if (!sub)
        return;
    demux_set_stream_wakeup_cb(sub->sh, NULL, NULL);
    if (sub->sd) {
        sub_reset(sub);
        sub->sd->driver->uninit(sub->sd);
    }
    talloc_free(sub->sd);
    pthread_mutex_destroy(&sub->lock);
    talloc_free(sub);
}