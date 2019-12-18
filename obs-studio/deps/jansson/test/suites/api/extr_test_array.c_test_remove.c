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
 int /*<<< orphan*/ * json_array_get (int /*<<< orphan*/ *,int) ; 
 scalar_t__ json_array_remove (int /*<<< orphan*/ *,int) ; 
 int json_array_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_integer (int) ; 

__attribute__((used)) static void test_remove(void)
{
    json_t *array, *five, *seven;
    int i;

    array = json_array();
    five = json_integer(5);
    seven = json_integer(7);

    if(!array)
        fail("unable to create array");
    if(!five)
        fail("unable to create integer");
    if(!seven)
        fail("unable to create integer");


    if(!json_array_remove(array, 0))
        fail("able to remove an unexisting index");


    if(json_array_append(array, five))
        fail("unable to append");

    if(!json_array_remove(array, 1))
        fail("able to remove an unexisting index");

    if(json_array_remove(array, 0))
        fail("unable to remove");

    if(json_array_size(array) != 0)
        fail("array size is invalid after removing");


    if(json_array_append(array, five) ||
       json_array_append(array, seven) ||
       json_array_append(array, five) ||
       json_array_append(array, seven))
        fail("unable to append");

    if(json_array_remove(array, 2))
        fail("unable to remove");

    if(json_array_size(array) != 3)
        fail("array size is invalid after removing");

    if(json_array_get(array, 0) != five ||
       json_array_get(array, 1) != seven ||
       json_array_get(array, 2) != seven)
        fail("remove works incorrectly");

    json_decref(array);

    array = json_array();
    for(i = 0; i < 4; i++) {
        json_array_append(array, five);
        json_array_append(array, seven);
    }
    if(json_array_size(array) != 8)
        fail("unable to append 8 items to array");

    /* Remove an element from a "full" array. */
    json_array_remove(array, 5);

    json_decref(five);
    json_decref(seven);
    json_decref(array);
}