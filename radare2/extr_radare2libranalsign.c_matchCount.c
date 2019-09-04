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

/* Variables and functions */
 int R_ABS (int) ; 

__attribute__((used)) static int matchCount(int a, int b) {
	int c = a - b;
	int m = a / 10;
	return R_ABS (c) < m;
}