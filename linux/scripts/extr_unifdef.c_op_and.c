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
typedef  scalar_t__ Linetype ;

/* Variables and functions */
 scalar_t__ LT_FALSE ; 
 scalar_t__ op_strict (int*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strictlogic ; 

__attribute__((used)) static Linetype op_and(int *p, Linetype at, int a, Linetype bt, int b) {
	if (!strictlogic && (at == LT_FALSE || bt == LT_FALSE))
		return (*p = 0, LT_FALSE);
	return op_strict(p, a && b, at, bt);
}