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
 int /*<<< orphan*/  r_anal_fcn_count_edges (int /*<<< orphan*/  const*,int*) ; 

__attribute__((used)) static int cmpedges(const void *_a, const void *_b) {
	const RAnalFunction *a = _a, *b = _b;
	int as, bs;
	r_anal_fcn_count_edges (a, &as);
	r_anal_fcn_count_edges (b, &bs);
	return (as > bs)? 1: (as < bs)? -1: 0;
}