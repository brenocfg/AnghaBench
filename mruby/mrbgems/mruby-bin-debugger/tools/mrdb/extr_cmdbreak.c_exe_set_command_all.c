#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int wcnt; int /*<<< orphan*/  dbg; } ;
typedef  TYPE_1__ mrdb_state ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_bool ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  (* all_command_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MRB_DEBUG_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  print_api_common_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_bool
exe_set_command_all(mrb_state *mrb, mrdb_state *mrdb, all_command_func func)
{
  int32_t ret = MRB_DEBUG_OK;

  if (mrdb->wcnt == 1) {
    ret = func(mrb, mrdb->dbg);
    print_api_common_error(ret);
    return TRUE;
  }
  return FALSE;
}