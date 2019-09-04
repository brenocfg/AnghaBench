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
 int /*<<< orphan*/  mpc_escape_input_raw_re ; 
 int /*<<< orphan*/  mpc_escape_output_raw_re ; 
 int /*<<< orphan*/ * mpcf_escape_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

mpc_val_t *mpcf_escape_regex(mpc_val_t *x) {
  mpc_val_t *y = mpcf_escape_new(x, mpc_escape_input_raw_re, mpc_escape_output_raw_re);
  free(x);
  return y;  
}