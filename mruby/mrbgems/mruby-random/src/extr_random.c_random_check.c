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
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  E_TYPE_ERROR ; 
 struct RClass* mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_istruct_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_is_kind_of (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct RClass*) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
random_check(mrb_state *mrb, mrb_value random) {
  struct RClass *c = mrb_class_get(mrb, "Random");
  if (!mrb_obj_is_kind_of(mrb, random, c) || !mrb_istruct_p(random)) {
    mrb_raise(mrb, E_TYPE_ERROR, "Random instance required");
  }
}