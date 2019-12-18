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
struct TYPE_6__ {int /*<<< orphan*/  name; TYPE_1__* mpctx; } ;
typedef  TYPE_2__ mpv_handle ;
struct TYPE_5__ {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  bstr0 (char*) ; 
 int /*<<< orphan*/  mp_input_parse_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int run_client_command (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mpv_command_string(mpv_handle *ctx, const char *args)
{
    return run_client_command(ctx,
        mp_input_parse_cmd(ctx->mpctx->input, bstr0((char*)args), ctx->name), NULL);
}