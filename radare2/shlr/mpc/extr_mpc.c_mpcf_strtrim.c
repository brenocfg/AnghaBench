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
 int /*<<< orphan*/ * mpcf_strtriml (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpcf_strtrimr (int /*<<< orphan*/ *) ; 

mpc_val_t *mpcf_strtrim(mpc_val_t *x) {
  return mpcf_strtriml(mpcf_strtrimr(x));
}