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
 int /*<<< orphan*/  E_TYPE_ERROR ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MRB_RANGE_OK ; 
 int /*<<< orphan*/  mrb_ary_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t mrb_fixnum (int /*<<< orphan*/  const) ; 
 scalar_t__ mrb_fixnum_p (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const) ; 
 scalar_t__ mrb_range_beg_len (int /*<<< orphan*/ *,int /*<<< orphan*/  const,size_t*,size_t*,size_t,int /*<<< orphan*/ ) ; 

mrb_value
mrb_get_values_at(mrb_state *mrb, mrb_value obj, mrb_int olen, mrb_int argc, const mrb_value *argv, mrb_value (*func)(mrb_state*, mrb_value, mrb_int))
{
  mrb_int i, j, beg, len;
  mrb_value result;
  result = mrb_ary_new(mrb);

  for (i = 0; i < argc; ++i) {
    if (mrb_fixnum_p(argv[i])) {
      mrb_ary_push(mrb, result, func(mrb, obj, mrb_fixnum(argv[i])));
    }
    else if (mrb_range_beg_len(mrb, argv[i], &beg, &len, olen, FALSE) == MRB_RANGE_OK) {
      mrb_int const end = olen < beg + len ? olen : beg + len;
      for (j = beg; j < end; ++j) {
        mrb_ary_push(mrb, result, func(mrb, obj, j));
      }

      for (; j < beg + len; ++j) {
        mrb_ary_push(mrb, result, mrb_nil_value());
      }
    }
    else {
      mrb_raisef(mrb, E_TYPE_ERROR, "invalid values selector: %v", argv[i]);
    }
  }

  return result;
}