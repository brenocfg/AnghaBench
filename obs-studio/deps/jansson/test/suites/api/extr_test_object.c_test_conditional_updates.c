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
 int json_integer_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_get (int /*<<< orphan*/ *,char*) ; 
 int json_object_size (int /*<<< orphan*/ *) ; 
 scalar_t__ json_object_update_existing (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ json_object_update_missing (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_pack (char*,char*,int,char*,int) ; 

__attribute__((used)) static void test_conditional_updates()
{
    json_t *object, *other;

    object = json_pack("{sisi}", "foo", 1, "bar", 2);
    other = json_pack("{sisi}", "foo", 3, "baz", 4);

    if(json_object_update_existing(object, other))
        fail("json_object_update_existing failed");

    if(json_object_size(object) != 2)
        fail("json_object_update_existing added new items");

    if(json_integer_value(json_object_get(object, "foo")) != 3)
        fail("json_object_update_existing failed to update existing key");

    if(json_integer_value(json_object_get(object, "bar")) != 2)
        fail("json_object_update_existing updated wrong key");

    json_decref(object);

    object = json_pack("{sisi}", "foo", 1, "bar", 2);

    if(json_object_update_missing(object, other))
        fail("json_object_update_missing failed");

    if(json_object_size(object) != 3)
        fail("json_object_update_missing didn't add new items");

    if(json_integer_value(json_object_get(object, "foo")) != 1)
        fail("json_object_update_missing updated existing key");

    if(json_integer_value(json_object_get(object, "bar")) != 2)
        fail("json_object_update_missing updated wrong key");

    if(json_integer_value(json_object_get(object, "baz")) != 4)
        fail("json_object_update_missing didn't add new items");

    json_decref(object);
    json_decref(other);
}