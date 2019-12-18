#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct backtrace_location {scalar_t__ method_id; int /*<<< orphan*/  lineno; int /*<<< orphan*/ * filename; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;
struct TYPE_2__ {scalar_t__ flags; } ;

/* Variables and functions */
 TYPE_1__* RDATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_type ; 
 scalar_t__ mrb_array_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_new_capa (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_data_check_get_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_format (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_cat_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_cat_lit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_sym_name (int /*<<< orphan*/ *,scalar_t__) ; 

mrb_value
mrb_unpack_backtrace(mrb_state *mrb, mrb_value backtrace)
{
  const struct backtrace_location *bt;
  mrb_int n, i;
  int ai;

  if (mrb_nil_p(backtrace)) {
  empty_backtrace:
    return mrb_ary_new_capa(mrb, 0);
  }
  if (mrb_array_p(backtrace)) return backtrace;
  bt = (struct backtrace_location*)mrb_data_check_get_ptr(mrb, backtrace, &bt_type);
  if (bt == NULL) goto empty_backtrace;
  n = (mrb_int)RDATA(backtrace)->flags;
  backtrace = mrb_ary_new_capa(mrb, n);
  ai = mrb_gc_arena_save(mrb);
  for (i = 0; i < n; i++) {
    const struct backtrace_location *entry = &bt[i];
    mrb_value btline;

    if (entry->filename == NULL) continue;
    btline = mrb_format(mrb, "%s:%d", entry->filename, entry->lineno);
    if (entry->method_id != 0) {
      mrb_str_cat_lit(mrb, btline, ":in ");
      mrb_str_cat_cstr(mrb, btline, mrb_sym_name(mrb, entry->method_id));
    }
    mrb_ary_push(mrb, backtrace, btline);
    mrb_gc_arena_restore(mrb, ai);
  }

  return backtrace;
}