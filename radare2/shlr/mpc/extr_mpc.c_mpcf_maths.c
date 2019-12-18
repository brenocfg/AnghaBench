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
typedef  int /*<<< orphan*/  mpc_val_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

mpc_val_t *mpcf_maths(int n, mpc_val_t **xs) {
  int **vs = (int**)xs;
  (void) n;
  
  if (strcmp(xs[1], "*") == 0) { *vs[0] *= *vs[2]; }
  if (strcmp(xs[1], "/") == 0) { *vs[0] /= *vs[2]; }
  if (strcmp(xs[1], "%") == 0) { *vs[0] %= *vs[2]; }
  if (strcmp(xs[1], "+") == 0) { *vs[0] += *vs[2]; }
  if (strcmp(xs[1], "-") == 0) { *vs[0] -= *vs[2]; }
  
  free(xs[1]); free(xs[2]);
  
  return xs[0];
}