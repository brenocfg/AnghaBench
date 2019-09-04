#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* mpctx; } ;
typedef  TYPE_2__ mpv_handle ;
struct TYPE_8__ {int /*<<< orphan*/  clients; } ;

/* Variables and functions */
 TYPE_2__* mp_new_client (int /*<<< orphan*/ ,char const*) ; 
 TYPE_2__* mpv_create () ; 
 int /*<<< orphan*/  mpv_wait_event (TYPE_2__*,int /*<<< orphan*/ ) ; 

mpv_handle *mpv_create_client(mpv_handle *ctx, const char *name)
{
    if (!ctx)
        return mpv_create();
    mpv_handle *new = mp_new_client(ctx->mpctx->clients, name);
    if (new)
        mpv_wait_event(new, 0); // set fuzzy_initialized
    return new;
}