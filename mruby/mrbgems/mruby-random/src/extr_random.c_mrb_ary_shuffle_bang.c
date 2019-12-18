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
typedef  int /*<<< orphan*/  rand_state ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;

/* Variables and functions */
 int RARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RARRAY_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_modify (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_ptr (int /*<<< orphan*/ ) ; 
 size_t mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  random_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * random_default_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * random_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  random_rand (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_ary_shuffle_bang(mrb_state *mrb, mrb_value ary)
{
  mrb_int i;
  mrb_value max;
  mrb_value r = mrb_nil_value();
  rand_state *random;

  if (RARRAY_LEN(ary) > 1) {
    mrb_get_args(mrb, "|o", &r);

    if (mrb_nil_p(r)) {
      random = random_default_state(mrb);
    }
    else {
      random_check(mrb, r);
      random = random_ptr(r);
    }
    mrb_ary_modify(mrb, mrb_ary_ptr(ary));
    max = mrb_fixnum_value(RARRAY_LEN(ary));
    for (i = RARRAY_LEN(ary) - 1; i > 0; i--)  {
      mrb_int j;
      mrb_value *ptr = RARRAY_PTR(ary);
      mrb_value tmp;

      j = mrb_fixnum(random_rand(mrb, random, max));

      tmp = ptr[i];
      ptr[i] = ptr[j];
      ptr[j] = tmp;
    }
  }

  return ary;
}