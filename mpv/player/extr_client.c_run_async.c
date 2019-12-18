#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* mpctx; } ;
typedef  TYPE_2__ mpv_handle ;
struct TYPE_5__ {int /*<<< orphan*/  dispatch; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_dispatch_enqueue (int /*<<< orphan*/ ,void (*) (void*),void*) ; 
 int reserve_reply (TYPE_2__*) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 

__attribute__((used)) static int run_async(mpv_handle *ctx, void (*fn)(void *fn_data), void *fn_data)
{
    int err = reserve_reply(ctx);
    if (err < 0) {
        talloc_free(fn_data);
        return err;
    }
    mp_dispatch_enqueue(ctx->mpctx->dispatch, fn, fn_data);
    return 0;
}