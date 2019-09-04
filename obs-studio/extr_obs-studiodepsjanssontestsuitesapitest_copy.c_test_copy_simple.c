#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int refcount; } ;
typedef  TYPE_1__ json_t ;

/* Variables and functions */
 int /*<<< orphan*/  fail (char*) ; 
 TYPE_1__* json_copy (TYPE_1__*) ; 
 int /*<<< orphan*/  json_decref (TYPE_1__*) ; 
 int /*<<< orphan*/  json_equal (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* json_false () ; 
 TYPE_1__* json_integer (int) ; 
 TYPE_1__* json_null () ; 
 TYPE_1__* json_real (int) ; 
 TYPE_1__* json_string (char*) ; 
 TYPE_1__* json_true () ; 

__attribute__((used)) static void test_copy_simple(void)
{
    json_t *value, *copy;

    if(json_copy(NULL))
        fail("copying NULL doesn't return NULL");

    /* true */
    value = json_true();
    copy = json_copy(value);
    if(value != copy)
        fail("copying true failed");
    json_decref(value);
    json_decref(copy);

    /* false */
    value = json_false();
    copy = json_copy(value);
    if(value != copy)
        fail("copying false failed");
    json_decref(value);
    json_decref(copy);

    /* null */
    value = json_null();
    copy = json_copy(value);
    if(value != copy)
        fail("copying null failed");
    json_decref(value);
    json_decref(copy);

    /* string */
    value = json_string("foo");
    if(!value)
        fail("unable to create a string");
    copy = json_copy(value);
    if(!copy)
        fail("unable to copy a string");
    if(copy == value)
        fail("copying a string doesn't copy");
    if(!json_equal(copy, value))
        fail("copying a string produces an inequal copy");
    if(value->refcount != 1 || copy->refcount != 1)
        fail("invalid refcounts");
    json_decref(value);
    json_decref(copy);

    /* integer */
    value = json_integer(543);
    if(!value)
        fail("unable to create an integer");
    copy = json_copy(value);
    if(!copy)
        fail("unable to copy an integer");
    if(copy == value)
        fail("copying an integer doesn't copy");
    if(!json_equal(copy, value))
        fail("copying an integer produces an inequal copy");
    if(value->refcount != 1 || copy->refcount != 1)
        fail("invalid refcounts");
    json_decref(value);
    json_decref(copy);

    /* real */
    value = json_real(123e9);
    if(!value)
        fail("unable to create a real");
    copy = json_copy(value);
    if(!copy)
        fail("unable to copy a real");
    if(copy == value)
        fail("copying a real doesn't copy");
    if(!json_equal(copy, value))
        fail("copying a real produces an inequal copy");
    if(value->refcount != 1 || copy->refcount != 1)
        fail("invalid refcounts");
    json_decref(value);
    json_decref(copy);
}