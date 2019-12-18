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
typedef  int /*<<< orphan*/  mrdb_state ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_bool ;
typedef  int /*<<< orphan*/  dbgcmd_state ;

/* Variables and functions */
 int /*<<< orphan*/  DBGST_PROMPT ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ exe_set_command_all (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exe_set_command_select (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_debug_delete_break ; 
 int /*<<< orphan*/  mrb_debug_delete_break_all ; 

dbgcmd_state
dbgcmd_delete(mrb_state *mrb, mrdb_state *mrdb)
{
  mrb_bool ret = FALSE;

  ret = exe_set_command_all(mrb, mrdb, mrb_debug_delete_break_all);
  if (ret != TRUE) {
    exe_set_command_select(mrb, mrdb, mrb_debug_delete_break);
  }

  return DBGST_PROMPT;
}