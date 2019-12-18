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
struct MPContext {int open_active; int /*<<< orphan*/  open_done; scalar_t__ open_format; scalar_t__ open_url; scalar_t__ open_cancel; int /*<<< orphan*/ * open_res_demuxer; int /*<<< orphan*/  open_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  TA_FREEP (scalar_t__*) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  demux_cancel_and_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_cancel_trigger (scalar_t__) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cancel_open(struct MPContext *mpctx)
{
    if (mpctx->open_cancel)
        mp_cancel_trigger(mpctx->open_cancel);

    if (mpctx->open_active)
        pthread_join(mpctx->open_thread, NULL);
    mpctx->open_active = false;

    if (mpctx->open_res_demuxer)
        demux_cancel_and_free(mpctx->open_res_demuxer);
    mpctx->open_res_demuxer = NULL;

    TA_FREEP(&mpctx->open_cancel);
    TA_FREEP(&mpctx->open_url);
    TA_FREEP(&mpctx->open_format);

    atomic_store(&mpctx->open_done, false);
}