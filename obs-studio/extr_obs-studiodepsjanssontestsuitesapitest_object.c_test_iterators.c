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
 int /*<<< orphan*/ * json_object () ; 
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/ *,char*) ; 
 void* json_object_iter (int /*<<< orphan*/ *) ; 
 void* json_object_iter_at (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  json_object_iter_key (void*) ; 
 int /*<<< orphan*/ * json_object_iter_next (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ json_object_iter_set (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_iter_value (void*) ; 
 scalar_t__ json_object_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_string (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_iterators()
{
    json_t *object, *foo, *bar, *baz;
    void *iter;

    if(json_object_iter(NULL))
        fail("able to iterate over NULL");

    if(json_object_iter_next(NULL, NULL))
        fail("able to increment an iterator on a NULL object");

    object = json_object();
    foo = json_string("foo");
    bar = json_string("bar");
    baz = json_string("baz");
    if(!object || !foo || !bar || !baz)
        fail("unable to create values");

    if(json_object_iter_next(object, NULL))
        fail("able to increment a NULL iterator");

    if(json_object_set(object, "a", foo) ||
       json_object_set(object, "b", bar) ||
       json_object_set(object, "c", baz))
        fail("unable to populate object");

    iter = json_object_iter(object);
    if(!iter)
        fail("unable to get iterator");
    if (strcmp(json_object_iter_key(iter), "a") != 0)
        fail("iterating doesn't yield keys in order");
    if (json_object_iter_value(iter) != foo)
        fail("iterating doesn't yield values in order");

    iter = json_object_iter_next(object, iter);
    if(!iter)
        fail("unable to increment iterator");
    if (strcmp(json_object_iter_key(iter), "b") != 0)
        fail("iterating doesn't yield keys in order");
    if (json_object_iter_value(iter) != bar)
        fail("iterating doesn't yield values in order");

    iter = json_object_iter_next(object, iter);
    if(!iter)
        fail("unable to increment iterator");
    if (strcmp(json_object_iter_key(iter), "c") != 0)
        fail("iterating doesn't yield keys in order");
    if (json_object_iter_value(iter) != baz)
        fail("iterating doesn't yield values in order");

    if(json_object_iter_next(object, iter) != NULL)
        fail("able to iterate over the end");

    if(json_object_iter_at(object, "foo"))
        fail("json_object_iter_at() succeeds for non-existent key");

    iter = json_object_iter_at(object, "b");
    if(!iter)
        fail("json_object_iter_at() fails for an existing key");

    if(strcmp(json_object_iter_key(iter), "b"))
        fail("iterating failed: wrong key");
    if(json_object_iter_value(iter) != bar)
        fail("iterating failed: wrong value");

    if(json_object_iter_set(object, iter, baz))
        fail("unable to set value at iterator");

    if(strcmp(json_object_iter_key(iter), "b"))
        fail("json_object_iter_key() fails after json_object_iter_set()");
    if(json_object_iter_value(iter) != baz)
        fail("json_object_iter_value() fails after json_object_iter_set()");
    if(json_object_get(object, "b") != baz)
        fail("json_object_get() fails after json_object_iter_set()");

    json_decref(object);
    json_decref(foo);
    json_decref(bar);
    json_decref(baz);
}