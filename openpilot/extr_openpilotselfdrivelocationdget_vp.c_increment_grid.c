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
 int W ; 
 int /*<<< orphan*/  free (double*) ; 
 int get_intersections (double*,double*,long long) ; 
 scalar_t__ malloc (long long) ; 

void increment_grid(double *grid, double *lines, long long n) {
  double *intersections = (double*) malloc(n*n*2*sizeof(double));
  int y, x, k;
  k = get_intersections(lines, intersections, n);
  for (int i=0; i < k; i++) {
    x = (int) (intersections[i*2 + 0] + 0.5);
    y = (int) (intersections[i*2 + 1] + 0.5);
    grid[y*(W+1) + x] += 1.;
  }
  free(intersections);
}