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
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/ * RARRAY_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_struct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_new_from_values (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_ary_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_obj_to_sym (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mrb_symbol_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_symbol_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_yield_with_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_struct_s_def(mrb_state *mrb, mrb_value klass)
{
  mrb_value name, rest;
  mrb_value *pargv;
  mrb_int argcnt;
  mrb_int i;
  mrb_value b, st;
  mrb_sym id;
  mrb_value *argv;
  mrb_int argc;

  name = mrb_nil_value();
  mrb_get_args(mrb, "*&", &argv, &argc, &b);
  if (argc == 0) { /* special case to avoid crash */
    mrb_raise(mrb, E_ARGUMENT_ERROR, "wrong number of arguments");
  }
  else {
    pargv = argv;
    argcnt = argc;
    if (argc > 0) {
      name = argv[0];
      if (mrb_symbol_p(name)) {
        /* 1stArgument:symbol -> name=nil rest=argv[0..n] */
        name = mrb_nil_value();
      }
      else {
        pargv++;
        argcnt--;
      }
    }
    rest = mrb_ary_new_from_values(mrb, argcnt, pargv);
    for (i=0; i<argcnt; i++) {
      id = mrb_obj_to_sym(mrb, RARRAY_PTR(rest)[i]);
      mrb_ary_set(mrb, rest, i, mrb_symbol_value(id));
    }
    st = make_struct(mrb, name, rest, mrb_class_ptr(klass));
    if (!mrb_nil_p(b)) {
      mrb_yield_with_class(mrb, b, 1, &st, st, mrb_class_ptr(st));
    }

    return st;
  }
  /* not reached */
  return mrb_nil_value();
}