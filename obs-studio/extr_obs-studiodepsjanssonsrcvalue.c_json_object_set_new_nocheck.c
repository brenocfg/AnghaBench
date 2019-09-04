#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_3__ {int /*<<< orphan*/  hashtable; } ;
typedef  TYPE_1__ json_object_t ;

/* Variables and functions */
 scalar_t__ hashtable_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_is_object (int /*<<< orphan*/ *) ; 
 TYPE_1__* json_to_object (int /*<<< orphan*/ *) ; 

int json_object_set_new_nocheck(json_t *json, const char *key, json_t *value)
{
    json_object_t *object;

    if(!value)
        return -1;

    if(!key || !json_is_object(json) || json == value)
    {
        json_decref(value);
        return -1;
    }
    object = json_to_object(json);

    if(hashtable_set(&object->hashtable, key, value))
    {
        json_decref(value);
        return -1;
    }

    return 0;
}