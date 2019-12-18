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
struct RProc {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_sym ;
struct TYPE_7__ {int /*<<< orphan*/  proc_class; } ;
typedef  TYPE_1__ mrb_state ;
typedef  int /*<<< orphan*/  mrb_method_t ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_METHOD_FROM_PROC (int /*<<< orphan*/ ,struct RProc*) ; 
 int /*<<< orphan*/  MRB_PROC_STRICT ; 
 int /*<<< orphan*/  MRB_TT_PROC ; 
 int /*<<< orphan*/  mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method_raw (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 scalar_t__ mrb_obj_alloc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_proc_copy (struct RProc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_proc_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_singleton_class (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_symbol_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mod_define_singleton_method(mrb_state *mrb, mrb_value self)
{
  struct RProc *p;
  mrb_method_t m;
  mrb_sym mid;
  mrb_value blk = mrb_nil_value();

  mrb_get_args(mrb, "n&!", &mid, &blk);
  p = (struct RProc*)mrb_obj_alloc(mrb, MRB_TT_PROC, mrb->proc_class);
  mrb_proc_copy(p, mrb_proc_ptr(blk));
  p->flags |= MRB_PROC_STRICT;
  MRB_METHOD_FROM_PROC(m, p);
  mrb_define_method_raw(mrb, mrb_class_ptr(mrb_singleton_class(mrb, self)), mid, m);
  return mrb_symbol_value(mid);
}