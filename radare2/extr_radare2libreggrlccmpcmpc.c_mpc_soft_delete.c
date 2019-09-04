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
 int /*<<< orphan*/  mpc_undefine_unretained (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpc_soft_delete(mpc_val_t *x) {
  mpc_undefine_unretained(x, 0);
}