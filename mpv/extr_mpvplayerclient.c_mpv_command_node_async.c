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
typedef  int /*<<< orphan*/  mpv_node ;
struct TYPE_4__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ mpv_handle ;

/* Variables and functions */
 int /*<<< orphan*/  mp_input_parse_cmd_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int run_async_cmd (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mpv_command_node_async(mpv_handle *ctx, uint64_t ud, mpv_node *args)
{
    return run_async_cmd(ctx, ud, mp_input_parse_cmd_node(ctx->log, args));
}