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
 int /*<<< orphan*/ * json_integer (int) ; 
 int /*<<< orphan*/ * json_object () ; 
 scalar_t__ json_object_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ json_object_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int json_object_size (int /*<<< orphan*/ *) ; 
 scalar_t__ json_object_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_update()
{
    json_t *object, *other, *nine, *ten;

    object = json_object();
    other = json_object();

    nine = json_integer(9);
    ten = json_integer(10);

    if(!object || !other)
        fail("unable to create object");
    if(!nine || !ten)
        fail("unable to create integer");


    /* update an empty object with an empty object */

    if(json_object_update(object, other))
        fail("unable to update an emtpy object with an empty object");

    if(json_object_size(object) != 0)
        fail("invalid size after update");

    if(json_object_size(other) != 0)
        fail("invalid size for updater after update");


    /* update an empty object with a nonempty object */

    if(json_object_set(other, "a", ten) ||
       json_object_set(other, "b", ten) ||
       json_object_set(other, "c", ten) ||
       json_object_set(other, "d", ten) ||
       json_object_set(other, "e", ten))
        fail("unable to set value");

    if(json_object_update(object, other))
        fail("unable to update an empty object");

    if(json_object_size(object) != 5)
        fail("invalid size after update");

    if(json_object_get(object, "a") != ten ||
       json_object_get(object, "b") != ten ||
       json_object_get(object, "c") != ten ||
       json_object_get(object, "d") != ten ||
       json_object_get(object, "e") != ten)
        fail("update works incorrectly");


    /* perform the same update again */

    if(json_object_update(object, other))
        fail("unable to update a non-empty object");

    if(json_object_size(object) != 5)
        fail("invalid size after update");

    if(json_object_get(object, "a") != ten ||
       json_object_get(object, "b") != ten ||
       json_object_get(object, "c") != ten ||
       json_object_get(object, "d") != ten ||
       json_object_get(object, "e") != ten)
        fail("update works incorrectly");


    /* update a nonempty object with a nonempty object with both old
       and new keys */

    if(json_object_clear(other))
        fail("clear failed");

    if(json_object_set(other, "a", nine) ||
       json_object_set(other, "b", nine) ||
       json_object_set(other, "f", nine) ||
       json_object_set(other, "g", nine) ||
       json_object_set(other, "h", nine))
        fail("unable to set value");

    if(json_object_update(object, other))
        fail("unable to update a nonempty object");

    if(json_object_size(object) != 8)
        fail("invalid size after update");

    if(json_object_get(object, "a") != nine ||
       json_object_get(object, "b") != nine ||
       json_object_get(object, "f") != nine ||
       json_object_get(object, "g") != nine ||
       json_object_get(object, "h") != nine)
        fail("update works incorrectly");

    json_decref(nine);
    json_decref(ten);
    json_decref(other);
    json_decref(object);
}