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
struct RClass {struct RClass* super; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 struct RClass* mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_iv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_obj_value (struct RClass*) ; 
 struct RClass* struct_class (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline mrb_value
struct_ivar_get(mrb_state *mrb, mrb_value cls, mrb_sym id)
{
  struct RClass* c = mrb_class_ptr(cls);
  struct RClass* sclass = struct_class(mrb);
  mrb_value ans;

  for (;;) {
    ans = mrb_iv_get(mrb, mrb_obj_value(c), id);
    if (!mrb_nil_p(ans)) return ans;
    c = c->super;
    if (c == sclass || c == 0)
      return mrb_nil_value();
  }
}