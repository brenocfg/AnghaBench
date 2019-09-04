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
typedef  float mpc_val_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (float*) ; 
 float* malloc (int) ; 
 float strtod (float*,int /*<<< orphan*/ *) ; 

mpc_val_t *mpcf_float(mpc_val_t *x) {
  float *y = malloc(sizeof(float));
  *y = strtod(x, NULL);
  free(x);
  return y;
}