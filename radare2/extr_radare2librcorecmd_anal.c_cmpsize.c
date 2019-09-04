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
 scalar_t__ r_anal_fcn_size (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int cmpsize (const void *_a, const void *_b) {
	const RAnalFunction *a = _a, *b = _b;
	int sa = (int)r_anal_fcn_size (a);
	int sb = (int)r_anal_fcn_size (b);
	return (sa > sb)? -1: (sa < sb)? 1 : 0;
}