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
typedef  int /*<<< orphan*/  OSSL_PROPERTY_LIST ;
typedef  int /*<<< orphan*/  OSSL_METHOD_STORE ;

/* Variables and functions */
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_ptr_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_ptr_ne (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 scalar_t__ add_property_names (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_method_store_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_method_store_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_parse_property (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ossl_prop_defn_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ossl_prop_defn_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_property_defn_cache(void)
{
    OSSL_METHOD_STORE *store;
    OSSL_PROPERTY_LIST *red, *blue;
    int r = 0;

    if (TEST_ptr(store = ossl_method_store_new(NULL))
        && add_property_names("red", "blue", NULL)
        && TEST_ptr(red = ossl_parse_property(NULL, "red"))
        && TEST_ptr(blue = ossl_parse_property(NULL, "blue"))
        && TEST_ptr_ne(red, blue)
        && TEST_true(ossl_prop_defn_set(NULL, "red", red))
        && TEST_true(ossl_prop_defn_set(NULL, "blue", blue))
        && TEST_ptr_eq(ossl_prop_defn_get(NULL, "red"), red)
        && TEST_ptr_eq(ossl_prop_defn_get(NULL, "blue"), blue))
        r = 1;
    ossl_method_store_free(store);
    return r;
}