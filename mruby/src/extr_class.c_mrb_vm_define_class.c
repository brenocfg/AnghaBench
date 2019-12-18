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
struct RClass {int /*<<< orphan*/  super; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  E_TYPE_ERROR ; 
 int /*<<< orphan*/  check_if_class_or_module (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct RClass* define_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct RClass*,struct RClass*) ; 
 int /*<<< orphan*/  mrb_class_inherited (int /*<<< orphan*/ *,struct RClass*,struct RClass*) ; 
 int /*<<< orphan*/  mrb_class_p (int /*<<< orphan*/ ) ; 
 struct RClass* mrb_class_ptr (int /*<<< orphan*/ ) ; 
 struct RClass* mrb_class_real (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_const_defined_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_const_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct RClass*
mrb_vm_define_class(mrb_state *mrb, mrb_value outer, mrb_value super, mrb_sym id)
{
  struct RClass *s;
  struct RClass *c;

  if (!mrb_nil_p(super)) {
    if (!mrb_class_p(super)) {
      mrb_raisef(mrb, E_TYPE_ERROR, "superclass must be a Class (%!v given)", super);
    }
    s = mrb_class_ptr(super);
  }
  else {
    s = 0;
  }
  check_if_class_or_module(mrb, outer);
  if (mrb_const_defined_at(mrb, outer, id)) {
    mrb_value old = mrb_const_get(mrb, outer, id);

    if (!mrb_class_p(old)) {
      mrb_raisef(mrb, E_TYPE_ERROR, "%!v is not a class", old);
    }
    c = mrb_class_ptr(old);
    if (s) {
      /* check super class */
      if (mrb_class_real(c->super) != s) {
        mrb_raisef(mrb, E_TYPE_ERROR, "superclass mismatch for class %v", old);
      }
    }
    return c;
  }
  c = define_class(mrb, id, s, mrb_class_ptr(outer));
  mrb_class_inherited(mrb, mrb_class_real(c->super), c);

  return c;
}