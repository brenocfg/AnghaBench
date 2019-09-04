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
struct TYPE_3__ {size_t entries; size_t size; int /*<<< orphan*/ ** table; } ;
typedef  TYPE_1__ json_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  array_copy (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  jsonp_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** jsonp_malloc (size_t) ; 
 size_t max (size_t,int) ; 

__attribute__((used)) static json_t **json_array_grow(json_array_t *array,
                                size_t amount,
                                int copy)
{
    size_t new_size;
    json_t **old_table, **new_table;

    if(array->entries + amount <= array->size)
        return array->table;

    old_table = array->table;

    new_size = max(array->size + amount, array->size * 2);
    new_table = jsonp_malloc(new_size * sizeof(json_t *));
    if(!new_table)
        return NULL;

    array->size = new_size;
    array->table = new_table;

    if(copy) {
        array_copy(array->table, 0, old_table, 0, array->entries);
        jsonp_free(old_table);
        return array->table;
    }

    return old_table;
}