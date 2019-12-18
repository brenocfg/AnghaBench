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
struct TYPE_4__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ mpv_handle ;

/* Variables and functions */
 int /*<<< orphan*/  mp_input_parse_cmd_strv (int /*<<< orphan*/ ,char const**) ; 
 int run_client_command (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mpv_command(mpv_handle *ctx, const char **args)
{
    return run_client_command(ctx, mp_input_parse_cmd_strv(ctx->log, args), NULL);
}