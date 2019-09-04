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
 int /*<<< orphan*/  json_object_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ json_object_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int json_object_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_clear()
{
    json_t *object, *ten;

    object = json_object();
    ten = json_integer(10);

    if(!object)
        fail("unable to create object");
    if(!ten)
        fail("unable to create integer");

    if(json_object_set(object, "a", ten) ||
       json_object_set(object, "b", ten) ||
       json_object_set(object, "c", ten) ||
       json_object_set(object, "d", ten) ||
       json_object_set(object, "e", ten))
        fail("unable to set value");

    if(json_object_size(object) != 5)
        fail("invalid size");

    json_object_clear(object);

    if(json_object_size(object) != 0)
        fail("invalid size after clear");

    json_decref(ten);
    json_decref(object);
}