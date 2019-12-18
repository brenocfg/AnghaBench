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
struct RObject {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  bind_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RObject* method_object_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_iv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_iv_set (int /*<<< orphan*/ *,struct RObject*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RObject*) ; 

__attribute__((used)) static mrb_value
unbound_method_bind(mrb_state *mrb, mrb_value self)
{
  struct RObject *me;
  mrb_value owner = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "_owner"));
  mrb_value name = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "_name"));
  mrb_value proc = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "_proc"));
  mrb_value klass = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "_klass"));
  mrb_value recv;

  mrb_get_args(mrb, "o", &recv);
  bind_check(mrb, recv, owner);
  me = method_object_alloc(mrb, mrb_class_get(mrb, "Method"));
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "_owner"), owner);
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "_recv"), recv);
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "_name"), name);
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "_proc"), proc);
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "_klass"), klass);

  return mrb_obj_value(me);
}