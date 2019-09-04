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
typedef  scalar_t__ OSSL_PROPERTY_IDX ;
typedef  int /*<<< orphan*/  OSSL_METHOD_STORE ;

/* Variables and functions */
 scalar_t__ TEST_int_eq (scalar_t__,scalar_t__) ; 
 scalar_t__ TEST_int_ne (scalar_t__,scalar_t__) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_method_store_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_method_store_new (int /*<<< orphan*/ *) ; 
 scalar_t__ ossl_property_name (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ ossl_property_value (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int test_property_string(void)
{
    OSSL_METHOD_STORE *store;
    int res = 0;
    OSSL_PROPERTY_IDX i, j;

    if (TEST_ptr(store = ossl_method_store_new(NULL))
        && TEST_int_eq(ossl_property_name(NULL, "fnord", 0), 0)
        && TEST_int_ne(ossl_property_name(NULL, "fnord", 1), 0)
        && TEST_int_ne(ossl_property_name(NULL, "name", 1), 0)
        /* Property value checks */
        && TEST_int_eq(ossl_property_value(NULL, "fnord", 0), 0)
        && TEST_int_ne(i = ossl_property_value(NULL, "no", 0), 0)
        && TEST_int_ne(j = ossl_property_value(NULL, "yes", 0), 0)
        && TEST_int_ne(i, j)
        && TEST_int_eq(ossl_property_value(NULL, "yes", 1), j)
        && TEST_int_eq(ossl_property_value(NULL, "no", 1), i)
        && TEST_int_ne(i = ossl_property_value(NULL, "illuminati", 1), 0)
        && TEST_int_eq(j = ossl_property_value(NULL, "fnord", 1), i + 1)
        && TEST_int_eq(ossl_property_value(NULL, "fnord", 1), j)
        /* Check name and values are distinct */
        && TEST_int_eq(ossl_property_value(NULL, "cold", 0), 0)
        && TEST_int_ne(ossl_property_name(NULL, "fnord", 0),
                       ossl_property_value(NULL, "fnord", 0)))
        res = 1;
    ossl_method_store_free(store);
    return res;
}