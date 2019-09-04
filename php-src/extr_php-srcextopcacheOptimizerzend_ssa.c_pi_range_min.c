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
typedef  int /*<<< orphan*/  zend_ssa_phi ;
typedef  int /*<<< orphan*/  zend_long ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_LONG_MAX ; 
 int /*<<< orphan*/  pi_range (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pi_range_min(zend_ssa_phi *phi, int var, zend_long val) {
	pi_range(phi, var, -1, val, ZEND_LONG_MAX, 0, 1, 0);
}