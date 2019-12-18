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
 int /*<<< orphan*/  json_deep_copy (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * json_object () ; 
 void* json_object_iter (int /*<<< orphan*/ *) ; 
 char* json_object_iter_key (void*) ; 
 void* json_object_iter_next (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * json_object_iter_value (void*) ; 
 int /*<<< orphan*/  json_object_set_new_nocheck (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static json_t *json_object_deep_copy(const json_t *object)
{
    json_t *result;
    void *iter;

    result = json_object();
    if(!result)
        return NULL;

    /* Cannot use json_object_foreach because object has to be cast
       non-const */
    iter = json_object_iter((json_t *)object);
    while(iter) {
        const char *key;
        const json_t *value;
        key = json_object_iter_key(iter);
        value = json_object_iter_value(iter);

        json_object_set_new_nocheck(result, key, json_deep_copy(value));
        iter = json_object_iter_next((json_t *)object, iter);
    }

    return result;
}