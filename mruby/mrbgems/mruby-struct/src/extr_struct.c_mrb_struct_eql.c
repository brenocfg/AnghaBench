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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;

/* Variables and functions */
 scalar_t__ RSTRUCT_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RSTRUCT_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_bug (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_eql (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_false_value () ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_obj_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_obj_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_true_value () ; 

__attribute__((used)) static mrb_value
mrb_struct_eql(mrb_state *mrb, mrb_value s)
{
  mrb_value s2;
  mrb_value *ptr, *ptr2;
  mrb_int i, len;

  mrb_get_args(mrb, "o", &s2);
  if (mrb_obj_equal(mrb, s, s2)) {
    return mrb_true_value();
  }
  if (mrb_obj_class(mrb, s) != mrb_obj_class(mrb, s2)) {
    return mrb_false_value();
  }
  if (RSTRUCT_LEN(s) != RSTRUCT_LEN(s2)) {
    mrb_bug(mrb, "inconsistent struct"); /* should never happen */
  }
  ptr = RSTRUCT_PTR(s);
  ptr2 = RSTRUCT_PTR(s2);
  len = RSTRUCT_LEN(s);
  for (i=0; i<len; i++) {
    if (!mrb_eql(mrb, ptr[i], ptr2[i])) {
      return mrb_false_value();
    }
  }

  return mrb_true_value();
}