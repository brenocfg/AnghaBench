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
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 scalar_t__ json_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_integer (int) ; 
 int /*<<< orphan*/ * json_real (double) ; 
 int /*<<< orphan*/ * json_string (char*) ; 
 int /*<<< orphan*/ * json_true () ; 

__attribute__((used)) static void test_equal_simple()
{
    json_t *value1, *value2;

    if(json_equal(NULL, NULL))
        fail("json_equal fails for two NULLs");

    value1 = json_true();
    if(json_equal(value1, NULL) || json_equal(NULL, value1))
        fail("json_equal fails for NULL");

    /* this covers true, false and null as they are singletons */
    if(!json_equal(value1, value1))
        fail("identical objects are not equal");
    json_decref(value1);

    /* integer */
    value1 = json_integer(1);
    value2 = json_integer(1);
    if(!value1 || !value2)
        fail("unable to create integers");
    if(!json_equal(value1, value2))
        fail("json_equal fails for two equal integers");
    json_decref(value2);

    value2 = json_integer(2);
    if(!value2)
        fail("unable to create an integer");
    if(json_equal(value1, value2))
        fail("json_equal fails for two inequal integers");

    json_decref(value1);
    json_decref(value2);

    /* real */
    value1 = json_real(1.2);
    value2 = json_real(1.2);
    if(!value1 || !value2)
        fail("unable to create reals");
    if(!json_equal(value1, value2))
        fail("json_equal fails for two equal reals");
    json_decref(value2);

    value2 = json_real(3.141592);
    if(!value2)
        fail("unable to create an real");
    if(json_equal(value1, value2))
        fail("json_equal fails for two inequal reals");

    json_decref(value1);
    json_decref(value2);

    /* string */
    value1 = json_string("foo");
    value2 = json_string("foo");
    if(!value1 || !value2)
        fail("unable to create strings");
    if(!json_equal(value1, value2))
        fail("json_equal fails for two equal strings");
    json_decref(value2);

    value2 = json_string("bar");
    if(!value2)
        fail("unable to create an string");
    if(json_equal(value1, value2))
        fail("json_equal fails for two inequal strings");

    json_decref(value1);
    json_decref(value2);
}