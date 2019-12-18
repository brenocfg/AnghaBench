#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  q_local; int /*<<< orphan*/  q_global; int /*<<< orphan*/  prop; } ;
typedef  int /*<<< orphan*/  OSSL_PROPERTY_LIST ;
typedef  int /*<<< orphan*/  OSSL_METHOD_STORE ;

/* Variables and functions */
 scalar_t__ TEST_int_ge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ add_property_names (char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* merge_tests ; 
 int /*<<< orphan*/  ossl_method_store_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_method_store_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_parse_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ossl_parse_query (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_property_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_property_match_count (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_property_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_property_merge(int n)
{
    OSSL_METHOD_STORE *store;
    OSSL_PROPERTY_LIST *q_global = NULL, *q_local = NULL;
    OSSL_PROPERTY_LIST *q_combined = NULL, *prop = NULL;
    int r = 0;

    if (TEST_ptr(store = ossl_method_store_new(NULL))
        && add_property_names("colour", "urn", "clouds", "pot", "day", "night",
                              NULL)
        && TEST_ptr(prop = ossl_parse_property(NULL, merge_tests[n].prop))
        && TEST_ptr(q_global = ossl_parse_query(NULL, merge_tests[n].q_global))
        && TEST_ptr(q_local = ossl_parse_query(NULL, merge_tests[n].q_local))
        && TEST_ptr(q_combined = ossl_property_merge(q_local, q_global))
        && TEST_int_ge(ossl_property_match_count(q_combined, prop), 0))
        r = 1;
    ossl_property_free(q_global);
    ossl_property_free(q_local);
    ossl_property_free(q_combined);
    ossl_property_free(prop);
    ossl_method_store_free(store);
    return r;
}