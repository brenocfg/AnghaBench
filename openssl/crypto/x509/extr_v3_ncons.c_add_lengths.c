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

__attribute__((used)) static int add_lengths(int *out, int a, int b)
{
    /* sk_FOO_num(NULL) returns -1 but is effectively 0 when iterating. */
    if (a < 0)
        a = 0;
    if (b < 0)
        b = 0;

    if (a > INT_MAX - b)
        return 0;
    *out = a + b;
    return 1;
}