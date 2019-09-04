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
struct TYPE_4__ {size_t entries; int /*<<< orphan*/ * table; } ;
typedef  TYPE_1__ json_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  array_copy (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  json_array_grow (TYPE_1__*,size_t,int) ; 
 int /*<<< orphan*/  json_incref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_is_array (int /*<<< orphan*/ *) ; 
 TYPE_1__* json_to_array (int /*<<< orphan*/ *) ; 

int json_array_extend(json_t *json, json_t *other_json)
{
    json_array_t *array, *other;
    size_t i;

    if(!json_is_array(json) || !json_is_array(other_json))
        return -1;
    array = json_to_array(json);
    other = json_to_array(other_json);

    if(!json_array_grow(array, other->entries, 1))
        return -1;

    for(i = 0; i < other->entries; i++)
        json_incref(other->table[i]);

    array_copy(array->table, array->entries, other->table, 0, other->entries);

    array->entries += other->entries;
    return 0;
}