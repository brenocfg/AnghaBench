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
typedef  scalar_t__ mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;
typedef  scalar_t__ mrb_float ;

/* Variables and functions */
 int /*<<< orphan*/  DROP_PRECISION (int,scalar_t__,scalar_t__) ; 
 scalar_t__ MRB_INT_MAX ; 
 scalar_t__ MRB_INT_MIN ; 
 scalar_t__ mrb_fixnum (scalar_t__) ; 
 scalar_t__ mrb_fixnum_p (scalar_t__) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ mrb_to_flo (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ rational_new (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static mrb_value
rational_s_new(mrb_state *mrb, mrb_value self)
{
  mrb_int numerator, denominator;

#ifdef MRB_WITHOUT_FLOAT
  mrb_get_args(mrb, "ii", &numerator, &denominator);
#else

#define DROP_PRECISION(cond, num, denom) \
  do { \
      while (cond) { \
        num /= 2; \
        denom /= 2; \
      } \
  } while (0)

  mrb_value numv, denomv;

  mrb_get_args(mrb, "oo", &numv, &denomv);
  if (mrb_fixnum_p(numv)) {
    numerator = mrb_fixnum(numv);

    if (mrb_fixnum_p(denomv)) {
      denominator = mrb_fixnum(denomv);
    }
    else {
      mrb_float denomf = mrb_to_flo(mrb, denomv);

      DROP_PRECISION(denomf < MRB_INT_MIN || denomf > MRB_INT_MAX, numerator, denomf);
      denominator = denomf;
    }
  }
  else {
    mrb_float numf = mrb_to_flo(mrb, numv);

    if (mrb_fixnum_p(denomv)) {
      denominator = mrb_fixnum(denomv);
    }
    else {
      mrb_float denomf = mrb_to_flo(mrb, denomv);

      DROP_PRECISION(denomf < MRB_INT_MIN || denomf > MRB_INT_MAX, numf, denomf);
      denominator = denomf;
    }

    DROP_PRECISION(numf < MRB_INT_MIN || numf > MRB_INT_MAX, numf, denominator);
    numerator = numf;
  }
#endif

  return rational_new(mrb, numerator, denominator);
}