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
struct TYPE_3__ {int print_no; int /*<<< orphan*/  dbg; } ;
typedef  TYPE_1__ mrdb_state ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  dbgcmd_state ;

/* Variables and functions */
 int /*<<< orphan*/  DBGST_PROMPT ; 
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_debug_eval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_str_cat_lit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,unsigned long,int /*<<< orphan*/ ) ; 

dbgcmd_state
dbgcmd_info_local(mrb_state *mrb, mrdb_state *mrdb)
{
  mrb_value result;
  mrb_value s;
  int ai;

  ai = mrb_gc_arena_save(mrb);

  result = mrb_debug_eval(mrb, mrdb->dbg, "local_variables", 0, NULL, 1);

  s = mrb_str_cat_lit(mrb, result, "\0");
  printf("$%lu = %s\n", (unsigned long)mrdb->print_no++, RSTRING_PTR(s));

  if (mrdb->print_no == 0) {
    mrdb->print_no = 1;
  }

  mrb_gc_arena_restore(mrb, ai);

  return DBGST_PROMPT;
}