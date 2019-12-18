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
typedef  struct RProc RObject ;
typedef  struct RProc RClass ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 struct RProc* method_object_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct RProc* mrb_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_obj_iv_set (int /*<<< orphan*/ *,struct RProc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RProc*) ; 
 int /*<<< orphan*/  mrb_search_method_owner (int /*<<< orphan*/ *,struct RProc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct RProc**,struct RProc**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_symbol_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_kernel_method(mrb_state *mrb, mrb_value self)
{
  struct RClass *owner;
  struct RProc *proc;
  struct RObject *me;
  mrb_sym name;

  mrb_get_args(mrb, "n", &name);

  mrb_search_method_owner(mrb, mrb_class(mrb, self), self, name, &owner, &proc, FALSE);

  me = method_object_alloc(mrb, mrb_class_get(mrb, "Method"));
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "_owner"), mrb_obj_value(owner));
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "_recv"), self);
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "_name"), mrb_symbol_value(name));
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "_proc"), proc ? mrb_obj_value(proc) : mrb_nil_value());
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "_klass"), mrb_obj_value(mrb_class(mrb, self)));

  return mrb_obj_value(me);
}