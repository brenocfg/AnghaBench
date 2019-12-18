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
 int /*<<< orphan*/ * json_array_get (int /*<<< orphan*/ *,size_t) ; 
 size_t json_array_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int json_array_equal(json_t *array1, json_t *array2)
{
    size_t i, size;

    size = json_array_size(array1);
    if(size != json_array_size(array2))
        return 0;

    for(i = 0; i < size; i++)
    {
        json_t *value1, *value2;

        value1 = json_array_get(array1, i);
        value2 = json_array_get(array2, i);

        if(!json_equal(value1, value2))
            return 0;
    }

    return 1;
}