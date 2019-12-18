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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ time_t ;
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_info (char*) ; 
 struct tm* localtime (scalar_t__*) ; 
 int /*<<< orphan*/  tbl_compare_testdata ; 
 int /*<<< orphan*/  tbl_testdata_neg ; 
 int /*<<< orphan*/  tbl_testdata_neg_64bit ; 
 int /*<<< orphan*/  tbl_testdata_pos ; 
 int /*<<< orphan*/  tbl_testdata_pos_64bit ; 
 int /*<<< orphan*/  test_table_compare ; 
 int /*<<< orphan*/  test_table_neg ; 
 int /*<<< orphan*/  test_table_neg_64bit ; 
 int /*<<< orphan*/  test_table_pos ; 
 int /*<<< orphan*/  test_table_pos_64bit ; 

int setup_tests(void)
{
    /*
     * On platforms where |time_t| is an unsigned integer, t will be a
     * positive number.
     *
     * We check if we're on a platform with a signed |time_t| with '!(t > 0)'
     * because some compilers are picky if you do 't < 0', or even 't <= 0'
     * if |t| is unsigned.
     */
    time_t t = -1;
    /*
     * On some platforms, |time_t| is signed, but a negative value is an
     * error, and using it with gmtime() or localtime() generates a NULL.
     * If that is the case, we can't perform tests on negative values.
     */
    struct tm *ptm = localtime(&t);

    ADD_ALL_TESTS(test_table_pos, OSSL_NELEM(tbl_testdata_pos));
    if (!(t > 0) && ptm != NULL) {
        TEST_info("Adding negative-sign time_t tests");
        ADD_ALL_TESTS(test_table_neg, OSSL_NELEM(tbl_testdata_neg));
    }
    if (sizeof(time_t) > sizeof(uint32_t)) {
        TEST_info("Adding 64-bit time_t tests");
        ADD_ALL_TESTS(test_table_pos_64bit, OSSL_NELEM(tbl_testdata_pos_64bit));
#ifndef __hpux
        if (!(t > 0) && ptm != NULL) {
            TEST_info("Adding negative-sign 64-bit time_t tests");
            ADD_ALL_TESTS(test_table_neg_64bit, OSSL_NELEM(tbl_testdata_neg_64bit));
        }
#endif
    }
    ADD_ALL_TESTS(test_table_compare, OSSL_NELEM(tbl_compare_testdata));
    return 1;
}