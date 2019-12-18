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
 int INT_MAX ; 

__attribute__((used)) static int next_pow2(int v)
{
    for (int x = 0; x < 30; x++) {
        if ((1 << x) >= v)
            return 1 << x;
    }
    return INT_MAX;
}