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
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ abs (int const) ; 

__attribute__((used)) static inline int
modulo_subtract(int x, int y, int mod)
{
    const int d1 = x - y;
    const int d2 = (x > y ? -mod : mod) + d1;
    ASSERT(0 <= x && x < mod && 0 <= y && y < mod);
    return abs(d1) > abs(d2) ? d2 : d1;
}