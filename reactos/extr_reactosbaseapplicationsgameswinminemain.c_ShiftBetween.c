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
typedef  scalar_t__ LONG ;

/* Variables and functions */

__attribute__((used)) static void ShiftBetween(LONG* x, LONG* y, LONG a, LONG b)
{
    if (*x < a) {
	*y += a - *x;
	*x = a;
    }
    else if (*y > b) {
	*x -= *y - b;
	*y = b;
    }
}