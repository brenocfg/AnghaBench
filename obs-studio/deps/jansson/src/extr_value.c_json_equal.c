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
#define  JSON_ARRAY 132 
#define  JSON_INTEGER 131 
#define  JSON_OBJECT 130 
#define  JSON_REAL 129 
#define  JSON_STRING 128 
 int json_array_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int json_integer_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int json_object_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int json_real_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int json_string_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int json_typeof (int /*<<< orphan*/ *) ; 

int json_equal(json_t *json1, json_t *json2)
{
    if(!json1 || !json2)
        return 0;

    if(json_typeof(json1) != json_typeof(json2))
        return 0;

    /* this covers true, false and null as they are singletons */
    if(json1 == json2)
        return 1;

    switch(json_typeof(json1)) {
        case JSON_OBJECT:
            return json_object_equal(json1, json2);
        case JSON_ARRAY:
            return json_array_equal(json1, json2);
        case JSON_STRING:
            return json_string_equal(json1, json2);
        case JSON_INTEGER:
            return json_integer_equal(json1, json2);
        case JSON_REAL:
            return json_real_equal(json1, json2);
        default:
            return 0;
    }
}