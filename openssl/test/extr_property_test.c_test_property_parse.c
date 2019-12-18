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
struct TYPE_2__ {int /*<<< orphan*/  e; int /*<<< orphan*/  query; int /*<<< orphan*/  defn; } ;
typedef  int /*<<< orphan*/  OSSL_PROPERTY_LIST ;
typedef  int /*<<< orphan*/  OSSL_METHOD_STORE ;

/* Variables and functions */
 scalar_t__ TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ add_property_names (char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_method_store_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_method_store_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_parse_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ossl_parse_query (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_property_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_property_match_count (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* parser_tests ; 

__attribute__((used)) static int test_property_parse(int n)
{
    OSSL_METHOD_STORE *store;
    OSSL_PROPERTY_LIST *p = NULL, *q = NULL;
    int r = 0;

    if (TEST_ptr(store = ossl_method_store_new(NULL))
        && add_property_names("sky", "groan", "cold", "today", "tomorrow", "n",
                              NULL)
        && TEST_ptr(p = ossl_parse_property(NULL, parser_tests[n].defn))
        && TEST_ptr(q = ossl_parse_query(NULL, parser_tests[n].query))
        && TEST_int_eq(ossl_property_match_count(q, p), parser_tests[n].e))
        r = 1;
    ossl_property_free(p);
    ossl_property_free(q);
    ossl_method_store_free(store);
    return r;
}