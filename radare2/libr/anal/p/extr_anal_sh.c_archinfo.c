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
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int R_ANAL_ARCHINFO_ALIGN ; 

__attribute__((used)) static int archinfo(RAnal *anal, int q) {
#if 0
	if (q == R_ANAL_ARCHINFO_ALIGN) {
		return 4;
	}
#endif
	return 2; /* :) */
}