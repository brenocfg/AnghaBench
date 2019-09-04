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
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int OPT_EOF ; 
#define  OPT_PROGRESS 130 
#define  OPT_SLOW 129 
#define  OPT_TEST_CASES 128 
 int max ; 
 int opt_next () ; 
 int /*<<< orphan*/  test_ed448 ; 
 int /*<<< orphan*/  test_x448 ; 
 int verbose ; 

int setup_tests(void)
{
    OPTION_CHOICE o;

    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_TEST_CASES:
            break;
        default:
            return 0;
        /*
         * The test vectors contain one test which takes a very long time to run
         * so we don't do that be default. Using the -f option will cause it to
         * be run.
         */
        case OPT_SLOW:
            max = 1000000;
            break;
        case OPT_PROGRESS:
            verbose = 1; /* Print progress dots */
            break;
        }
    }

    ADD_TEST(test_x448);
    ADD_TEST(test_ed448);
    return 1;
}