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
 double sqrt (int) ; 

double legacy_wald(aug_bitgen_t *aug_state, double mean, double scale) {
  double U, X, Y;
  double mu_2l;

  mu_2l = mean / (2 * scale);
  Y = legacy_gauss(aug_state);
  Y = mean * Y * Y;
  X = mean + mu_2l * (Y - sqrt(4 * scale * Y + Y * Y));
  U = legacy_double(aug_state);
  if (U <= mean / (mean + X)) {
    return X;
  } else {
    return mean * mean / X;
  }
}