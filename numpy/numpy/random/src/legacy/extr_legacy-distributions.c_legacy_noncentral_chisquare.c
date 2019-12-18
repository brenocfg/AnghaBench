#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bit_generator; } ;
typedef  TYPE_1__ aug_bitgen_t ;

/* Variables and functions */
 double NPY_NAN ; 
 double legacy_chisquare (TYPE_1__*,double) ; 
 double legacy_gauss (TYPE_1__*) ; 
 scalar_t__ npy_isnan (double) ; 
 long random_poisson (int /*<<< orphan*/ ,double) ; 
 double sqrt (double) ; 

double legacy_noncentral_chisquare(aug_bitgen_t *aug_state, double df,
                                   double nonc) {
  double out;
  if (nonc == 0) {
    return legacy_chisquare(aug_state, df);
  }
  if (1 < df) {
    const double Chi2 = legacy_chisquare(aug_state, df - 1);
    const double n = legacy_gauss(aug_state) + sqrt(nonc);
    return Chi2 + n * n;
  } else {
    const long i = random_poisson(aug_state->bit_generator, nonc / 2.0);
    out = legacy_chisquare(aug_state, df + 2 * i);
    /* Insert nan guard here to avoid changing the stream */
    if (npy_isnan(nonc)){
      return NPY_NAN;
    } else {
    return out;
    }
  }
}