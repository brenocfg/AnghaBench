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

/* Variables and functions */
 int /*<<< orphan*/  MRB_TT_ARRAY ; 
 int /*<<< orphan*/  mrb_ary_new_from_values (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_check_convert_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_f_array(mrb_state *mrb, mrb_value self)
{
  mrb_value arg, tmp;

  mrb_get_args(mrb, "o", &arg);
  tmp = mrb_check_convert_type(mrb, arg, MRB_TT_ARRAY, "Array", "to_a");
  if (mrb_nil_p(tmp)) {
    return mrb_ary_new_from_values(mrb, 1, &arg);
  }

  return tmp;
}