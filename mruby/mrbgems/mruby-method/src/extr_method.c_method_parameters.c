#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct RProc {struct RClass* c; } ;
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_7__ {struct RClass* proc_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_ary_new_from_values (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_funcall (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_iv_get (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 struct RProc* mrb_proc_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_symbol_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
method_parameters(mrb_state *mrb, mrb_value self)
{
  mrb_value proc = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "_proc"));
  struct RProc *rproc;
  struct RClass *orig;
  mrb_value ret;

  if (mrb_nil_p(proc)) {
    mrb_value rest = mrb_symbol_value(mrb_intern_lit(mrb, "rest"));
    mrb_value arest = mrb_ary_new_from_values(mrb, 1, &rest);
    return mrb_ary_new_from_values(mrb, 1, &arest);
  }

  rproc = mrb_proc_ptr(proc);
  orig = rproc->c;
  rproc->c = mrb->proc_class;
  ret = mrb_funcall(mrb, proc, "parameters", 0);
  rproc->c = orig;
  return ret;
}