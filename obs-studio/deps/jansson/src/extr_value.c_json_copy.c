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
#define  JSON_ARRAY 135 
#define  JSON_FALSE 134 
#define  JSON_INTEGER 133 
#define  JSON_NULL 132 
#define  JSON_OBJECT 131 
#define  JSON_REAL 130 
#define  JSON_STRING 129 
#define  JSON_TRUE 128 
 int /*<<< orphan*/ * json_array_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_integer_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_real_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_string_copy (int /*<<< orphan*/ *) ; 
 int json_typeof (int /*<<< orphan*/ *) ; 

json_t *json_copy(json_t *json)
{
    if(!json)
        return NULL;

    switch(json_typeof(json)) {
        case JSON_OBJECT:
            return json_object_copy(json);
        case JSON_ARRAY:
            return json_array_copy(json);
        case JSON_STRING:
            return json_string_copy(json);
        case JSON_INTEGER:
            return json_integer_copy(json);
        case JSON_REAL:
            return json_real_copy(json);
        case JSON_TRUE:
        case JSON_FALSE:
        case JSON_NULL:
            return json;
        default:
            return NULL;
    }

    return NULL;
}