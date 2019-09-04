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
 scalar_t__ OSSL_NELEM (scalar_t__*) ; 
 int opt_num_rest () ; 
 char** opt_rest () ; 
 int /*<<< orphan*/  test_printf_stderr (char*,int,...) ; 
 scalar_t__* used ; 

void opt_check_usage(void)
{
    int i;
    char **argv = opt_rest();
    int n, arg_count = opt_num_rest();

    if (arg_count > (int)OSSL_NELEM(used))
        n = (int)OSSL_NELEM(used);
    else
        n = arg_count;
    for (i = 0; i < n; i++) {
        if (used[i] == 0)
            test_printf_stderr("Warning ignored command-line argument %d: %s\n",
                               i, argv[i]);
    }
    if (i < arg_count)
        test_printf_stderr("Warning arguments %d and later unchecked\n", i);
}