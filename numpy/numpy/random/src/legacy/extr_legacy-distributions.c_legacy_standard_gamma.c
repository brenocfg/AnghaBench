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
typedef  int /*<<< orphan*/  aug_bitgen_t ;

/* Variables and functions */
 double legacy_double (int /*<<< orphan*/ *) ; 
 double legacy_gauss (int /*<<< orphan*/ *) ; 
 double legacy_standard_exponential (int /*<<< orphan*/ *) ; 
 int log (double) ; 
 double pow (double,int) ; 
 int sqrt (int) ; 

double legacy_standard_gamma(aug_bitgen_t *aug_state, double shape) {
  double b, c;
  double U, V, X, Y;

  if (shape == 1.0) {
    return legacy_standard_exponential(aug_state);
  }
  else if (shape == 0.0) {
    return 0.0;
  } else if (shape < 1.0) {
    for (;;) {
      U = legacy_double(aug_state);
      V = legacy_standard_exponential(aug_state);
      if (U <= 1.0 - shape) {
        X = pow(U, 1. / shape);
        if (X <= V) {
          return X;
        }
      } else {
        Y = -log((1 - U) / shape);
        X = pow(1.0 - shape + shape * Y, 1. / shape);
        if (X <= (V + Y)) {
          return X;
        }
      }
    }
  } else {
    b = shape - 1. / 3.;
    c = 1. / sqrt(9 * b);
    for (;;) {
      do {
        X = legacy_gauss(aug_state);
        V = 1.0 + c * X;
      } while (V <= 0.0);

      V = V * V * V;
      U = legacy_double(aug_state);
      if (U < 1.0 - 0.0331 * (X * X) * (X * X))
        return (b * V);
      if (log(U) < 0.5 * X * X + b * (1. - V + log(V)))
        return (b * V);
    }
  }
}