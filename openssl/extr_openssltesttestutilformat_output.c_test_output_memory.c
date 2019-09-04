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
 int /*<<< orphan*/  test_fail_memory_common (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,unsigned char const*,size_t,unsigned char const*,size_t) ; 

void test_output_memory(const char *name, const unsigned char *m, size_t l)
{
    test_fail_memory_common("memory", NULL, 0, NULL, NULL, NULL, name,
                            m, l, m, l);
}