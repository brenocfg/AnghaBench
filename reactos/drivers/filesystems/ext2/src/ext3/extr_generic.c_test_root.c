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
typedef  int /*<<< orphan*/  ext3_group_t ;

/* Variables and functions */

__attribute__((used)) static inline int test_root(ext3_group_t a, ext3_group_t b)
{
    ext3_group_t num = b;

    while (a > num)
        num *= b;
    return num == a;
}