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

/* Variables and functions */
 double fma (double,double,double) ; 

__attribute__((used)) static void my_sincosm1pi (double a, double *restrict res)
  {
  double s = a * a;
  /* Approximate cos(pi*x)-1 for x in [-0.25,0.25] */
  double r =     -1.0369917389758117e-4;
  r = fma (r, s,  1.9294935641298806e-3);
  r = fma (r, s, -2.5806887942825395e-2);
  r = fma (r, s,  2.3533063028328211e-1);
  r = fma (r, s, -1.3352627688538006e+0);
  r = fma (r, s,  4.0587121264167623e+0);
  r = fma (r, s, -4.9348022005446790e+0);
  double c = r*s;
  /* Approximate sin(pi*x) for x in [-0.25,0.25] */
  r =             4.6151442520157035e-4;
  r = fma (r, s, -7.3700183130883555e-3);
  r = fma (r, s,  8.2145868949323936e-2);
  r = fma (r, s, -5.9926452893214921e-1);
  r = fma (r, s,  2.5501640398732688e+0);
  r = fma (r, s, -5.1677127800499516e+0);
  s = s * a;
  r = r * s;
  s = fma (a, 3.1415926535897931e+0, r);
  res[0] = c;
  res[1] = s;
  }