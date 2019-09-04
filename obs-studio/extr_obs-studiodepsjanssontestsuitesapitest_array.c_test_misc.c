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
 scalar_t__ json_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ json_array_append_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_array_get (int /*<<< orphan*/ *,int) ; 
 scalar_t__ json_array_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ json_array_set_new (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int json_array_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_integer (int) ; 
 int json_integer_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_is_integer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_misc(void)
{
    json_t *array, *five, *seven, *value;
    size_t i;

    array = json_array();
    five = json_integer(5);
    seven = json_integer(7);

    if(!array)
        fail("unable to create array");
    if(!five || !seven)
        fail("unable to create integer");

    if(json_array_size(array) != 0)
        fail("empty array has nonzero size");

    if(!json_array_append(array, NULL))
        fail("able to append NULL");

    if(json_array_append(array, five))
        fail("unable to append");

    if(json_array_size(array) != 1)
        fail("wrong array size");

    value = json_array_get(array, 0);
    if(!value)
        fail("unable to get item");
    if(value != five)
        fail("got wrong value");

    if(json_array_append(array, seven))
        fail("unable to append value");

    if(json_array_size(array) != 2)
        fail("wrong array size");

    value = json_array_get(array, 1);
    if(!value)
        fail("unable to get item");
    if(value != seven)
        fail("got wrong value");

    if(json_array_set(array, 0, seven))
        fail("unable to set value");

    if(!json_array_set(array, 0, NULL))
        fail("able to set NULL");

    if(json_array_size(array) != 2)
        fail("wrong array size");

    value = json_array_get(array, 0);
    if(!value)
        fail("unable to get item");
    if(value != seven)
        fail("got wrong value");

    if(json_array_get(array, 2) != NULL)
        fail("able to get value out of bounds");

    if(!json_array_set(array, 2, seven))
        fail("able to set value out of bounds");

    for(i = 2; i < 30; i++) {
        if(json_array_append(array, seven))
            fail("unable to append value");

        if(json_array_size(array) != i + 1)
            fail("wrong array size");
    }

    for(i = 0; i < 30; i++) {
        value = json_array_get(array, i);
        if(!value)
            fail("unable to get item");
        if(value != seven)
            fail("got wrong value");
    }

    if(json_array_set_new(array, 15, json_integer(123)))
        fail("unable to set new value");

    value = json_array_get(array, 15);
    if(!json_is_integer(value) || json_integer_value(value) != 123)
        fail("json_array_set_new works incorrectly");

    if(!json_array_set_new(array, 15, NULL))
        fail("able to set_new NULL value");

    if(json_array_append_new(array, json_integer(321)))
        fail("unable to append new value");

    value = json_array_get(array, json_array_size(array) - 1);
    if(!json_is_integer(value) || json_integer_value(value) != 321)
        fail("json_array_append_new works incorrectly");

    if(!json_array_append_new(array, NULL))
        fail("able to append_new NULL value");

    json_decref(five);
    json_decref(seven);
    json_decref(array);
}