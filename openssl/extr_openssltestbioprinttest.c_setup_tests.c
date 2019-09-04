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
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int OPT_EOF ; 
#define  OPT_PRINT 129 
#define  OPT_TEST_CASES 128 
 int /*<<< orphan*/  jf_data ; 
 int justprint ; 
 int /*<<< orphan*/  nelem (int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 int /*<<< orphan*/  pw_params ; 
 int /*<<< orphan*/  test_big ; 
 int /*<<< orphan*/  test_fp ; 
 int /*<<< orphan*/  test_j ; 
 int /*<<< orphan*/  test_zu ; 
 int /*<<< orphan*/  zu_data ; 

int setup_tests(void)
{
    OPTION_CHOICE o;

    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_PRINT:
            justprint = 1;
            break;
        case OPT_TEST_CASES:
            break;
        default:
            return 0;
        }
    }

    ADD_TEST(test_big);
    ADD_ALL_TESTS(test_fp, nelem(pw_params));
    ADD_ALL_TESTS(test_zu, nelem(zu_data));
    ADD_ALL_TESTS(test_j, nelem(jf_data));
    return 1;
}