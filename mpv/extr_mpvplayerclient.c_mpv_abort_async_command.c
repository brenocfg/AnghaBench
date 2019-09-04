#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  mpctx; } ;
typedef  TYPE_1__ mpv_handle ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_EVENT_COMMAND_REPLY ; 
 int /*<<< orphan*/  abort_async (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mpv_abort_async_command(mpv_handle *ctx, uint64_t reply_userdata)
{
    abort_async(ctx->mpctx, ctx, MPV_EVENT_COMMAND_REPLY, reply_userdata);
}