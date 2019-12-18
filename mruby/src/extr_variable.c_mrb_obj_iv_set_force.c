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
struct RObject {scalar_t__ iv; } ;
struct RBasic {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  assign_class_name (int /*<<< orphan*/ *,struct RObject*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iv_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iv_put (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_write_barrier (int /*<<< orphan*/ *,struct RBasic*) ; 

void
mrb_obj_iv_set_force(mrb_state *mrb, struct RObject *obj, mrb_sym sym, mrb_value v)
{
  assign_class_name(mrb, obj, sym, v);
  if (!obj->iv) {
    obj->iv = iv_new(mrb);
  }
  iv_put(mrb, obj->iv, sym, v);
  mrb_write_barrier(mrb, (struct RBasic*)obj);
}