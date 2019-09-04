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
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * json_array () ; 
 int /*<<< orphan*/  json_array_append_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_integer (int) ; 
 int /*<<< orphan*/ * json_object () ; 
 int /*<<< orphan*/  json_object_set_new (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void encode_twice()
{
    /* Encode an empty object/array, add an item, encode again */

    json_t *json;
    char *result;

    json = json_object();
    result = json_dumps(json, 0);
    if(!result || strcmp(result, "{}"))
      fail("json_dumps failed");
    free(result);

    json_object_set_new(json, "foo", json_integer(5));
    result = json_dumps(json, 0);
    if(!result || strcmp(result, "{\"foo\": 5}"))
      fail("json_dumps failed");
    free(result);

    json_decref(json);

    json = json_array();
    result = json_dumps(json, 0);
    if(!result || strcmp(result, "[]"))
      fail("json_dumps failed");
    free(result);

    json_array_append_new(json, json_integer(5));
    result = json_dumps(json, 0);
    if(!result || strcmp(result, "[5]"))
      fail("json_dumps failed");
    free(result);

    json_decref(json);
}