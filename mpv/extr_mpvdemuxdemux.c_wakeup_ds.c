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
struct demux_stream {int need_wakeup; TYPE_1__* in; int /*<<< orphan*/  wakeup_cb_ctx; int /*<<< orphan*/  (* wakeup_cb ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  wakeup; int /*<<< orphan*/  wakeup_cb_ctx; int /*<<< orphan*/  (* wakeup_cb ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wakeup_ds(struct demux_stream *ds)
{
    if (ds->need_wakeup) {
        if (ds->wakeup_cb) {
            ds->wakeup_cb(ds->wakeup_cb_ctx);
        } else if (ds->in->wakeup_cb) {
            ds->in->wakeup_cb(ds->in->wakeup_cb_ctx);
        }
        ds->need_wakeup = false;
        pthread_cond_signal(&ds->in->wakeup);
    }
}