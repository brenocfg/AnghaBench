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
struct TYPE_5__ {size_t entries; struct TYPE_5__* table; } ;
typedef  TYPE_1__ json_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  json_decref (TYPE_1__) ; 
 int /*<<< orphan*/  jsonp_free (TYPE_1__*) ; 

__attribute__((used)) static void json_delete_array(json_array_t *array)
{
    size_t i;

    for(i = 0; i < array->entries; i++)
        json_decref(array->table[i]);

    jsonp_free(array->table);
    jsonp_free(array);
}