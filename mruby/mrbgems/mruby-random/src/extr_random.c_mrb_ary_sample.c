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
typedef  int mrb_int ;
typedef  int /*<<< orphan*/  mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int RARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RARRAY_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_new_capa (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 size_t mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int rand_uint32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * random_default_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * random_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_ary_sample(mrb_state *mrb, mrb_value ary)
{
  mrb_int n = 0;
  mrb_bool given;
  mrb_value r = mrb_nil_value();
  rand_state *random;
  mrb_int len;

  mrb_get_args(mrb, "|i?o", &n, &given, &r);
  if (mrb_nil_p(r)) {
    random = random_default_state(mrb);
  }
  else {
    random_check(mrb, r);
    random = random_ptr(r);
  }
  len = RARRAY_LEN(ary);
  if (!given) {                 /* pick one element */
    switch (len) {
    case 0:
      return mrb_nil_value();
    case 1:
      return RARRAY_PTR(ary)[0];
    default:
      return RARRAY_PTR(ary)[rand_uint32(random) % len];
    }
  }
  else {
    mrb_value result;
    mrb_int i, j;

    if (n < 0) mrb_raise(mrb, E_ARGUMENT_ERROR, "negative sample number");
    if (n > len) n = len;
    result = mrb_ary_new_capa(mrb, n);
    for (i=0; i<n; i++) {
      mrb_int r;

      for (;;) {
      retry:
        r = (mrb_int)(rand_uint32(random) % len);

        for (j=0; j<i; j++) {
          if (mrb_fixnum(RARRAY_PTR(result)[j]) == r) {
            goto retry;         /* retry if duplicate */
          }
        }
        break;
      }
      mrb_ary_push(mrb, result, mrb_fixnum_value(r));
    }
    for (i=0; i<n; i++) {
      mrb_ary_set(mrb, result, i, RARRAY_PTR(ary)[mrb_fixnum(RARRAY_PTR(result)[i])]);
    }
    return result;
  }
}