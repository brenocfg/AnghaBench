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
typedef  int /*<<< orphan*/  RAnalFunction ;

/* Variables and functions */
 scalar_t__ r_anal_fcn_realsize (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int compareSize(const RAnalFunction *a, const RAnalFunction *b) {
	// return a && b && a->_size < b->_size;
	return a && b && r_anal_fcn_realsize (a) > r_anal_fcn_realsize (b);
}