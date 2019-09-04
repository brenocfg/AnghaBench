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
 int /*<<< orphan*/ * json_deep_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loads (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/ *,char const*) ; 
 void* json_object_iter (int /*<<< orphan*/ *) ; 
 char* json_object_iter_key (void*) ; 
 void* json_object_iter_next (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * json_object_iter_value (void*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static void test_deep_copy_object(void)
{
    const char *json_object_text =
        "{\"foo\": \"bar\", \"a\": 1, \"b\": 3.141592, \"c\": [1,2,3,4]}";

    const char *keys[] = {"foo", "a", "b", "c"};
    int i;

    json_t *object, *copy;
    void *iter;

    object = json_loads(json_object_text, 0, NULL);
    if(!object)
        fail("unable to parse an object");

    copy = json_deep_copy(object);
    if(!copy)
        fail("unable to deep copy an object");
    if(copy == object)
        fail("deep copying an object doesn't copy");
    if(!json_equal(copy, object))
        fail("deep copying an object produces an inequal copy");

    i = 0;
    iter = json_object_iter(object);
    while(iter)
    {
        const char *key;
        json_t *value1, *value2;

        key = json_object_iter_key(iter);
        value1 = json_object_iter_value(iter);
        value2 = json_object_get(copy, key);

        if(value1 == value2)
            fail("deep copying an object doesn't copy its items");

        if (strcmp(key, keys[i]) != 0)
            fail("deep copying an object doesn't preserve key order");

        iter = json_object_iter_next(object, iter);
        i++;
    }

    json_decref(object);
    json_decref(copy);
}