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
 int /*<<< orphan*/ * json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object () ; 
 scalar_t__ json_object_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_circular()
{
    json_t *object1, *object2;

    object1 = json_object();
    object2 = json_object();
    if(!object1 || !object2)
        fail("unable to create object");

    /* the simple case is checked */
    if(json_object_set(object1, "a", object1) == 0)
        fail("able to set self");

    /* create circular references */
    if(json_object_set(object1, "a", object2) ||
       json_object_set(object2, "a", object1))
        fail("unable to set value");

    /* circularity is detected when dumping */
    if(json_dumps(object1, 0) != NULL)
        fail("able to dump circulars");

    /* decref twice to deal with the circular references */
    json_decref(object1);
    json_decref(object2);
    json_decref(object1);
}