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
 scalar_t__ json_array_append_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ json_array_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ json_array_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_true () ; 

__attribute__((used)) static void test_circular()
{
    json_t *array1, *array2;

    /* the simple cases are checked */

    array1 = json_array();
    if(!array1)
        fail("unable to create array");

    if(json_array_append(array1, array1) == 0)
        fail("able to append self");

    if(json_array_insert(array1, 0, array1) == 0)
        fail("able to insert self");

    if(json_array_append_new(array1, json_true()))
        fail("failed to append true");

    if(json_array_set(array1, 0, array1) == 0)
        fail("able to set self");

    json_decref(array1);


    /* create circular references */

    array1 = json_array();
    array2 = json_array();
    if(!array1 || !array2)
        fail("unable to create array");

    if(json_array_append(array1, array2) ||
       json_array_append(array2, array1))
        fail("unable to append");

    /* circularity is detected when dumping */
    if(json_dumps(array1, 0) != NULL)
        fail("able to dump circulars");

    /* decref twice to deal with the circular references */
    json_decref(array1);
    json_decref(array2);
    json_decref(array1);
}