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
 scalar_t__ json_array_clear (int /*<<< orphan*/ *) ; 
 int json_array_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_integer (int) ; 

__attribute__((used)) static void test_clear(void)
{
    json_t *array, *five, *seven;
    int i;

    array = json_array();
    five = json_integer(5);
    seven = json_integer(7);

    if(!array)
        fail("unable to create array");
    if(!five || !seven)
        fail("unable to create integer");

    for(i = 0; i < 10; i++) {
        if(json_array_append(array, five))
            fail("unable to append");
    }
    for(i = 0; i < 10; i++) {
        if(json_array_append(array, seven))
            fail("unable to append");
    }

    if(json_array_size(array) != 20)
        fail("array size is invalid after appending");

    if(json_array_clear(array))
        fail("unable to clear");

    if(json_array_size(array) != 0)
        fail("array size is invalid after clearing");

    json_decref(five);
    json_decref(seven);
    json_decref(array);
}