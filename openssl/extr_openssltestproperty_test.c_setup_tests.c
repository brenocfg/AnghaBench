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
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  definition_tests ; 
 int /*<<< orphan*/  merge_tests ; 
 int /*<<< orphan*/  parser_tests ; 
 int /*<<< orphan*/  test_definition_compares ; 
 int /*<<< orphan*/  test_property ; 
 int /*<<< orphan*/  test_property_defn_cache ; 
 int /*<<< orphan*/  test_property_merge ; 
 int /*<<< orphan*/  test_property_parse ; 
 int /*<<< orphan*/  test_property_string ; 
 int /*<<< orphan*/  test_query_cache_stochastic ; 
 int /*<<< orphan*/  test_register_deregister ; 

int setup_tests(void)
{
    ADD_TEST(test_property_string);
    ADD_ALL_TESTS(test_property_parse, OSSL_NELEM(parser_tests));
    ADD_ALL_TESTS(test_property_merge, OSSL_NELEM(merge_tests));
    ADD_TEST(test_property_defn_cache);
    ADD_ALL_TESTS(test_definition_compares, OSSL_NELEM(definition_tests));
    ADD_TEST(test_register_deregister);
    ADD_TEST(test_property);
    ADD_TEST(test_query_cache_stochastic);
    return 1;
}