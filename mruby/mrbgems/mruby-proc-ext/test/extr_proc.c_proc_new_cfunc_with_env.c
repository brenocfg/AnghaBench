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
struct RProc {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_method_t ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_METHOD_FROM_PROC (int /*<<< orphan*/ ,struct RProc*) ; 
 int /*<<< orphan*/  mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method_raw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 struct RProc* mrb_proc_new_cfunc_with_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_symbol_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_func_name ; 

__attribute__((used)) static mrb_value
proc_new_cfunc_with_env(mrb_state *mrb, mrb_value self)
{
  mrb_sym n;
  mrb_value n_val;
  mrb_method_t m;
  struct RProc *p;
  mrb_get_args(mrb, "n", &n);
  n_val = mrb_symbol_value(n);
  p = mrb_proc_new_cfunc_with_env(mrb, return_func_name, 1, &n_val);
  MRB_METHOD_FROM_PROC(m, p);
  mrb_define_method_raw(mrb, mrb_class_ptr(self), n, m);
  return self;
}