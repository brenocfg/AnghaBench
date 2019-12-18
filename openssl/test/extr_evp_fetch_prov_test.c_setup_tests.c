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
#define  OPT_ALG_FETCH_TYPE 133 
 int OPT_EOF ; 
#define  OPT_ERR 132 
#define  OPT_FETCH_FAILURE 131 
#define  OPT_FETCH_PROPERTY 130 
#define  OPT_TEST_CASES 129 
#define  OPT_USE_DEFAULTCTX 128 
 void* alg ; 
 int /*<<< orphan*/  expected_fetch_result ; 
 void* fetch_property ; 
 void* opt_arg () ; 
 int opt_next () ; 
 scalar_t__ strcmp (void*,char*) ; 
 int /*<<< orphan*/  test_EVP_CIPHER_fetch ; 
 int /*<<< orphan*/  test_EVP_MD_fetch ; 
 int use_default_ctx ; 

int setup_tests(void)
{
    OPTION_CHOICE o;

    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_ALG_FETCH_TYPE:
            alg = opt_arg();
            break;
        case OPT_FETCH_PROPERTY:
            fetch_property = opt_arg();
            break;
        case OPT_FETCH_FAILURE:
            expected_fetch_result = 0;
            break;
        case OPT_USE_DEFAULTCTX:
            use_default_ctx = 1;
            break;
        case OPT_TEST_CASES:
           break;
        default:
        case OPT_ERR:
            return 0;
        }
    }
    if (strcmp(alg, "digest") == 0)
        ADD_TEST(test_EVP_MD_fetch);
    else
        ADD_TEST(test_EVP_CIPHER_fetch);
    return 1;
}