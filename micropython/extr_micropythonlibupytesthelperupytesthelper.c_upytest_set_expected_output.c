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
 char const* test_exp_output ; 
 unsigned int test_exp_output_len ; 
 int test_failed ; 
 unsigned int test_rem_output_len ; 

void upytest_set_expected_output(const char *output, unsigned len) {
    test_exp_output = output;
    test_exp_output_len = test_rem_output_len = len;
    test_failed = false;
}