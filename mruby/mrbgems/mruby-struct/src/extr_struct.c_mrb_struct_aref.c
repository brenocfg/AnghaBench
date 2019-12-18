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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_check_intern_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_name_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_string_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_symbol (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_symbol_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_aref_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_aref_sym (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_struct_aref(mrb_state *mrb, mrb_value s)
{
  mrb_value idx;

  mrb_get_args(mrb, "o", &idx);
  if (mrb_string_p(idx)) {
    mrb_value sym = mrb_check_intern_str(mrb, idx);

    if (mrb_nil_p(sym)) {
      mrb_name_error(mrb, mrb_intern_str(mrb, idx), "no member '%v' in struct", idx);
    }
    idx = sym;
  }
  if (mrb_symbol_p(idx)) {
    return struct_aref_sym(mrb, s, mrb_symbol(idx));
  }
  return struct_aref_int(mrb, s, mrb_int(mrb, idx));
}