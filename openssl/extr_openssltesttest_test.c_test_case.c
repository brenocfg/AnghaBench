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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int test_case(int expected, const char *test, int result)
{
    if (result != expected) {
        fprintf(stderr, "# FATAL: %s != %d\n", test, expected);
        return 0;
    }
    return 1;
}