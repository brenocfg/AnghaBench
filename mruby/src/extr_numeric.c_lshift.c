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
typedef  int mrb_int ;
typedef  int mrb_float ;

/* Variables and functions */
 int INFINITY ; 
 int MRB_INT_MAX ; 
 int MRB_INT_MIN ; 
 int NUMERIC_SHIFT_WIDTH_MAX ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_float_value (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static mrb_value
lshift(mrb_state *mrb, mrb_int val, mrb_int width)
{
  if (width < 0) {              /* mrb_int overflow */
#ifdef MRB_WITHOUT_FLOAT
    return mrb_fixnum_value(0);
#else
    return mrb_float_value(mrb, INFINITY);
#endif
  }
  if (val > 0) {
    if ((width > NUMERIC_SHIFT_WIDTH_MAX) ||
        (val   > (MRB_INT_MAX >> width))) {
#ifdef MRB_WITHOUT_FLOAT
      return mrb_fixnum_value(-1);
#else
      goto bit_overflow;
#endif
    }
    return mrb_fixnum_value(val << width);
  }
  else {
    if ((width > NUMERIC_SHIFT_WIDTH_MAX) ||
        (val   <= (MRB_INT_MIN >> width))) {
#ifdef MRB_WITHOUT_FLOAT
      return mrb_fixnum_value(0);
#else
      goto bit_overflow;
#endif
    }
    return mrb_fixnum_value(val * ((mrb_int)1 << width));
  }

#ifndef MRB_WITHOUT_FLOAT
bit_overflow:
  {
    mrb_float f = (mrb_float)val;
    while (width--) {
      f *= 2;
    }
    return mrb_float_value(mrb, f);
  }
#endif
}