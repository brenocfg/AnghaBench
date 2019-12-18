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
 int /*<<< orphan*/  json_integer (int) ; 
 int /*<<< orphan*/ * json_object () ; 
 int /*<<< orphan*/  json_object_del (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  json_object_set_new (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_string (char*) ; 

__attribute__((used)) static void test_equal_object()
{
    json_t *object1, *object2;

    object1 = json_object();
    object2 = json_object();
    if(!object1 || !object2)
        fail("unable to create objects");

    if(!json_equal(object1, object2))
        fail("json_equal fails for two empty objects");

    json_object_set_new(object1, "a", json_integer(1));
    json_object_set_new(object2, "a", json_integer(1));
    json_object_set_new(object1, "b", json_string("foo"));
    json_object_set_new(object2, "b", json_string("foo"));
    json_object_set_new(object1, "c", json_integer(2));
    json_object_set_new(object2, "c", json_integer(2));
    if(!json_equal(object1, object2))
        fail("json_equal fails for two equal objects");

    json_object_del(object2, "c");
    if(json_equal(object1, object2))
        fail("json_equal fails for two inequal objects");

    json_object_set_new(object2, "c", json_integer(3));
    if(json_equal(object1, object2))
        fail("json_equal fails for two inequal objects");

    json_object_del(object2, "c");
    json_object_set_new(object2, "d", json_integer(2));
    if(json_equal(object1, object2))
        fail("json_equal fails for two inequal objects");

    json_decref(object1);
    json_decref(object2);
}