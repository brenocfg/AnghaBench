#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_5__ {size_t entries; int /*<<< orphan*/ ** table; } ;
typedef  TYPE_1__ json_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  array_copy (int /*<<< orphan*/ **,size_t,int /*<<< orphan*/ **,size_t,size_t) ; 
 int /*<<< orphan*/  array_move (TYPE_1__*,size_t,size_t,size_t) ; 
 int /*<<< orphan*/ ** json_array_grow (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_is_array (int /*<<< orphan*/ *) ; 
 TYPE_1__* json_to_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonp_free (int /*<<< orphan*/ **) ; 

int json_array_insert_new(json_t *json, size_t index, json_t *value)
{
    json_array_t *array;
    json_t **old_table;

    if(!value)
        return -1;

    if(!json_is_array(json) || json == value) {
        json_decref(value);
        return -1;
    }
    array = json_to_array(json);

    if(index > array->entries) {
        json_decref(value);
        return -1;
    }

    old_table = json_array_grow(array, 1, 0);
    if(!old_table) {
        json_decref(value);
        return -1;
    }

    if(old_table != array->table) {
        array_copy(array->table, 0, old_table, 0, index);
        array_copy(array->table, index + 1, old_table, index,
                   array->entries - index);
        jsonp_free(old_table);
    }
    else
        array_move(array, index + 1, index, array->entries - index);

    array->table[index] = value;
    array->entries++;

    return 0;
}