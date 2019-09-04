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
 int /*<<< orphan*/  json_delete_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_delete_integer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_delete_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_delete_real (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_delete_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_to_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_to_integer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_to_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_to_real (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_to_string (int /*<<< orphan*/ *) ; 
 int json_typeof (int /*<<< orphan*/ *) ; 

void json_delete(json_t *json)
{
    if (!json)
        return;

    switch(json_typeof(json)) {
        case JSON_OBJECT:
            json_delete_object(json_to_object(json));
            break;
        case JSON_ARRAY:
            json_delete_array(json_to_array(json));
            break;
        case JSON_STRING:
            json_delete_string(json_to_string(json));
            break;
        case JSON_INTEGER:
            json_delete_integer(json_to_integer(json));
            break;
        case JSON_REAL:
            json_delete_real(json_to_real(json));
            break;
        default:
            return;
    }

    /* json_delete is not called for true, false or null */
}