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
 double H ; 
 double W ; 

int get_intersections(double *lines, double *intersections, long long n) {
  double D, Dx, Dy;
  double x, y;
  double *L1, *L2;
  int k = 0;
  for (int i=0; i < n; i++) {
    for (int j=0; j < n; j++) {
      L1 = lines + i*3;
      L2 = lines + j*3;
      D = L1[0] * L2[1] - L1[1] * L2[0];
      Dx = L1[2] * L2[1] - L1[1] * L2[2];
      Dy = L1[0] * L2[2] - L1[2] * L2[0];
      // only intersect lines from different quadrants and only left-right crossing
      if ((D != 0) && (L1[0]*L2[0]*L1[1]*L2[1] < 0) && (L1[1]*L2[1] < 0)){
        x = Dx / D;
        y = Dy / D;
        if ((0 < x) &&
            (x < W) &&
            (0 < y) &&
            (y < H)){
          intersections[k*2 + 0] = x;
          intersections[k*2 + 1] = y;
          k++;
        }
      }
    }
  }
  return k;
}