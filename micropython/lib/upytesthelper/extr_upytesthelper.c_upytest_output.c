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
typedef  scalar_t__ mp_uint_t ;

/* Variables and functions */
 int memcmp (char const*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  mp_hal_stdout_tx_strn_cooked (char const*,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,int,char const,char const) ; 
 char const* test_exp_output ; 
 scalar_t__ test_exp_output_len ; 
 int test_failed ; 
 scalar_t__ test_rem_output_len ; 

void upytest_output(const char *str, mp_uint_t len) {
    if (!test_failed) {
        if (len > test_rem_output_len) {
            test_failed = true;
        } else {
            test_failed = memcmp(test_exp_output, str, len);
            #if 0
            if (test_failed) {
                printf("failed after char %u, within %d chars, res: %d\n",
                    test_exp_output_len - test_rem_output_len, (int)len, test_failed);
                for (int i = 0; i < len; i++) {
                    if (str[i] != test_exp_output[i]) {
                        printf("%d %02x %02x\n", i, str[i], test_exp_output[i]);
                    }
                }
            }
            #endif
            test_exp_output += len;
            test_rem_output_len -= len;
        }
    }
    mp_hal_stdout_tx_strn_cooked(str, len);
}