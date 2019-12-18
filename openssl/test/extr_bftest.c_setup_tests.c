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
typedef  int OPTION_CHOICE ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int KEY_TEST_NUM ; 
 int NUM_TESTS ; 
 int OPT_EOF ; 
#define  OPT_PRINT 129 
#define  OPT_TEST_CASES 128 
 int /*<<< orphan*/ * bf_key ; 
 int /*<<< orphan*/  cbc_data ; 
 int /*<<< orphan*/  ebcdic2ascii (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 int /*<<< orphan*/  print_test_data () ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bf_cbc ; 
 int /*<<< orphan*/  test_bf_cfb64 ; 
 int /*<<< orphan*/  test_bf_ecb ; 
 int /*<<< orphan*/  test_bf_ecb_raw ; 
 int /*<<< orphan*/  test_bf_ofb64 ; 
 int /*<<< orphan*/  test_bf_set_key ; 

int setup_tests(void)
{
#ifndef OPENSSL_NO_BF
    OPTION_CHOICE o;
# ifdef CHARSET_EBCDIC
    int n;
    ebcdic2ascii(cbc_data, cbc_data, strlen(cbc_data));
    for (n = 0; n < 2; n++) {
        ebcdic2ascii(bf_key[n], bf_key[n], strlen(bf_key[n]));
    }
# endif

    while ((o = opt_next()) != OPT_EOF) {
        switch(o) {
        case OPT_PRINT:
            print_test_data();
            return 1;
        case OPT_TEST_CASES:
            break;
        default:
           return 0;
        }
    }

    ADD_ALL_TESTS(test_bf_ecb_raw, 2);
    ADD_ALL_TESTS(test_bf_ecb, NUM_TESTS);
    ADD_ALL_TESTS(test_bf_set_key, KEY_TEST_NUM-1);
    ADD_TEST(test_bf_cbc);
    ADD_TEST(test_bf_cfb64);
    ADD_TEST(test_bf_ofb64);
#endif
    return 1;
}