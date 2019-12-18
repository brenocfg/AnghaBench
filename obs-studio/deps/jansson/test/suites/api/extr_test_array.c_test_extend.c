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
 scalar_t__ json_array_extend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_array_get (int /*<<< orphan*/ *,int) ; 
 int json_array_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_integer (int) ; 

__attribute__((used)) static void test_extend(void)
{
    json_t *array1, *array2, *five, *seven;
    int i;

    array1 = json_array();
    array2 = json_array();
    five = json_integer(5);
    seven = json_integer(7);

    if(!array1 || !array2)
        fail("unable to create array");
    if(!five || !seven)
        fail("unable to create integer");

    for(i = 0; i < 10; i++) {
        if(json_array_append(array1, five))
            fail("unable to append");
    }
    for(i = 0; i < 10; i++) {
        if(json_array_append(array2, seven))
            fail("unable to append");
    }

    if(json_array_size(array1) != 10 || json_array_size(array2) != 10)
        fail("array size is invalid after appending");

    if(json_array_extend(array1, array2))
        fail("unable to extend");

    for(i = 0; i < 10; i++) {
        if(json_array_get(array1, i) != five)
            fail("invalid array contents after extending");
    }
    for(i = 10; i < 20; i++) {
        if(json_array_get(array1, i) != seven)
            fail("invalid array contents after extending");
    }

    json_decref(five);
    json_decref(seven);
    json_decref(array1);
    json_decref(array2);
}