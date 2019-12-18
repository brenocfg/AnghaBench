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
 struct RClass* E_TYPE_ERROR ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_rescue_exceptions (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct RClass**) ; 
 int /*<<< orphan*/  protect_cb ; 

__attribute__((used)) static mrb_value
run_rescue_exceptions(mrb_state *mrb, mrb_value self)
{
  mrb_value b, r;
  struct RClass *cls[1];
  mrb_get_args(mrb, "oo", &b, &r);
  cls[0] = E_TYPE_ERROR;
  return mrb_rescue_exceptions(mrb, protect_cb, b, protect_cb, r, 1, cls);
}