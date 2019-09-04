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
 int /*<<< orphan*/ * json_array () ; 
 int /*<<< orphan*/  json_array_append_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_array_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 scalar_t__ json_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_integer (int) ; 
 int /*<<< orphan*/  json_string (char*) ; 

__attribute__((used)) static void test_equal_array()
{
    json_t *array1, *array2;

    array1 = json_array();
    array2 = json_array();
    if(!array1 || !array2)
        fail("unable to create arrays");

    if(!json_equal(array1, array2))
        fail("json_equal fails for two empty arrays");

    json_array_append_new(array1, json_integer(1));
    json_array_append_new(array2, json_integer(1));
    json_array_append_new(array1, json_string("foo"));
    json_array_append_new(array2, json_string("foo"));
    json_array_append_new(array1, json_integer(2));
    json_array_append_new(array2, json_integer(2));
    if(!json_equal(array1, array2))
        fail("json_equal fails for two equal arrays");

    json_array_remove(array2, 2);
    if(json_equal(array1, array2))
        fail("json_equal fails for two inequal arrays");

    json_array_append_new(array2, json_integer(3));
    if(json_equal(array1, array2))
        fail("json_equal fails for two inequal arrays");

    json_decref(array1);
    json_decref(array2);
}