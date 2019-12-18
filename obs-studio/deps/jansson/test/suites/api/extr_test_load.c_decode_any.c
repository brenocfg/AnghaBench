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
typedef  int /*<<< orphan*/  json_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_DECODE_ANY ; 
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_is_integer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_is_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_is_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_is_true (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loads (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void decode_any()
{
    json_t *json;
    json_error_t error;

    json = json_loads("\"foo\"", JSON_DECODE_ANY, &error);
    if (!json || !json_is_string(json))
        fail("json_load decoded any failed - string");
    json_decref(json);

    json = json_loads("42", JSON_DECODE_ANY, &error);
    if (!json || !json_is_integer(json))
        fail("json_load decoded any failed - integer");
    json_decref(json);

    json = json_loads("true", JSON_DECODE_ANY, &error);
    if (!json || !json_is_true(json))
        fail("json_load decoded any failed - boolean");
    json_decref(json);

    json = json_loads("null", JSON_DECODE_ANY, &error);
    if (!json || !json_is_null(json))
        fail("json_load decoded any failed - null");
    json_decref(json);
}