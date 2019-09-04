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
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

mpc_val_t *mpcf_strfold(int n, mpc_val_t **xs) {
  int i;
  size_t l = 0;
  
  if (n == 0) { return calloc(1, 1); }
  
  for (i = 0; i < n; i++) { l += strlen(xs[i]); }
  
  xs[0] = realloc(xs[0], l + 1);
  
  for (i = 1; i < n; i++) {
    strcat(xs[0], xs[i]); free(xs[i]);
  }
  
  return xs[0];
}