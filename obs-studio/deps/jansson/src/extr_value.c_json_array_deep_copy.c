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
 int /*<<< orphan*/ * json_array () ; 
 int /*<<< orphan*/  json_array_append_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_array_get (int /*<<< orphan*/  const*,size_t) ; 
 size_t json_array_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  json_deep_copy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static json_t *json_array_deep_copy(const json_t *array)
{
    json_t *result;
    size_t i;

    result = json_array();
    if(!result)
        return NULL;

    for(i = 0; i < json_array_size(array); i++)
        json_array_append_new(result, json_deep_copy(json_array_get(array, i)));

    return result;
}