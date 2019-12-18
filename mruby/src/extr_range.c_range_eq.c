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
struct RRange {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  RANGE_BEG (struct RRange*) ; 
 int /*<<< orphan*/  RANGE_END (struct RRange*) ; 
 scalar_t__ RANGE_EXCL (struct RRange*) ; 
 int /*<<< orphan*/  mrb_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_false_value () ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_obj_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_obj_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_is_instance_of (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RRange* mrb_range_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_true_value () ; 

__attribute__((used)) static mrb_value
range_eq(mrb_state *mrb, mrb_value range)
{
  struct RRange *rr;
  struct RRange *ro;
  mrb_value obj;
  mrb_bool v1, v2;

  mrb_get_args(mrb, "o", &obj);

  if (mrb_obj_equal(mrb, range, obj)) return mrb_true_value();
  if (!mrb_obj_is_instance_of(mrb, obj, mrb_obj_class(mrb, range))) { /* same class? */
    return mrb_false_value();
  }

  rr = mrb_range_ptr(mrb, range);
  ro = mrb_range_ptr(mrb, obj);
  v1 = mrb_equal(mrb, RANGE_BEG(rr), RANGE_BEG(ro));
  v2 = mrb_equal(mrb, RANGE_END(rr), RANGE_END(ro));
  if (!v1 || !v2 || RANGE_EXCL(rr) != RANGE_EXCL(ro)) {
    return mrb_false_value();
  }
  return mrb_true_value();
}