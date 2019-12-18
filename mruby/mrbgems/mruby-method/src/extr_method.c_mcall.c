#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_sym ;
struct TYPE_13__ {TYPE_2__* c; } ;
typedef  TYPE_3__ mrb_state ;
struct TYPE_12__ {TYPE_1__* ci; } ;
struct TYPE_11__ {int /*<<< orphan*/  mid; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARRAY_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_new_from_values (TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_ary_unshift (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_funcall_argv (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_funcall_with_block (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (TYPE_3__*,char*) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_yield_with_class (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct RClass*) ; 

__attribute__((used)) static mrb_value
mcall(mrb_state *mrb, mrb_value recv, mrb_value proc, mrb_value name, struct RClass *owner,
      int argc, mrb_value *argv, mrb_value block)
{
  mrb_value ret;
  mrb_sym orig_mid = mrb->c->ci->mid;

  mrb->c->ci->mid = mrb_symbol(name);
  if (mrb_nil_p(proc)) {
    mrb_value missing_argv = mrb_ary_new_from_values(mrb, argc, argv);
    mrb_ary_unshift(mrb, missing_argv, name);
    ret = mrb_funcall_argv(mrb, recv, mrb_intern_lit(mrb, "method_missing"), argc + 1, RARRAY_PTR(missing_argv));
  }
  else if (!mrb_nil_p(block)) {
    /*
      workaround since `mrb_yield_with_class` does not support passing block as parameter
      need new API that initializes `mrb->c->stack[argc+1]` with block passed by argument
    */
    ret = mrb_funcall_with_block(mrb, recv, mrb_symbol(name), argc, argv, block);
  }
  else {
    ret = mrb_yield_with_class(mrb, proc, argc, argv, recv, owner);
  }
  mrb->c->ci->mid = orig_mid;
  return ret;
}