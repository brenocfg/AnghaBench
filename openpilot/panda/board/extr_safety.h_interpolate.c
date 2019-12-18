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
struct lookup_t {float* y; float* x; } ;

/* Variables and functions */

float interpolate(struct lookup_t xy, float x) {

  int size = sizeof(xy.x) / sizeof(xy.x[0]);
  float ret = xy.y[size - 1];  // default output is last point

  // x is lower than the first point in the x array. Return the first point
  if (x <= xy.x[0]) {
    ret = xy.y[0];

  } else {
    // find the index such that (xy.x[i] <= x < xy.x[i+1]) and linearly interp
    for (int i=0; i < (size - 1); i++) {
      if (x < xy.x[i+1]) {
        float x0 = xy.x[i];
        float y0 = xy.y[i];
        float dx = xy.x[i+1] - x0;
        float dy = xy.y[i+1] - y0;
        // dx should not be zero as xy.x is supposed ot be monotonic
        if (dx <= 0.) {
          dx = 0.0001;
        }
        ret = (dy * (x - x0) / dx) + y0;
        break;
      }
    }
  }
  return ret;
}