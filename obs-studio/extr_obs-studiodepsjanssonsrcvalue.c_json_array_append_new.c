#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_4__ {size_t entries; int /*<<< orphan*/ ** table; } ;
typedef  TYPE_1__ json_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  json_array_grow (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_is_array (int /*<<< orphan*/ *) ; 
 TYPE_1__* json_to_array (int /*<<< orphan*/ *) ; 

int json_array_append_new(json_t *json, json_t *value)
{
    json_array_t *array;

    if(!value)
        return -1;

    if(!json_is_array(json) || json == value)
    {
        json_decref(value);
        return -1;
    }
    array = json_to_array(json);

    if(!json_array_grow(array, 1, 1)) {
        json_decref(value);
        return -1;
    }

    array->table[array->entries] = value;
    array->entries++;

    return 0;
}