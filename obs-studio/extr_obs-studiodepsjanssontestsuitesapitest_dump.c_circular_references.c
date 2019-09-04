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
 int /*<<< orphan*/  json_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_array_append_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_array_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object () ; 
 int /*<<< orphan*/  json_object_del (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  json_object_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_object_set_new (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void circular_references()
{
    /* Construct a JSON object/array with a circular reference:

       object: {"a": {"b": {"c": <circular reference to $.a>}}}
       array: [[[<circular reference to the $[0] array>]]]

       Encode it, remove the circular reference and encode again.
    */

    json_t *json;
    char *result;

    json = json_object();
    json_object_set_new(json, "a", json_object());
    json_object_set_new(json_object_get(json, "a"), "b", json_object());
    json_object_set(json_object_get(json_object_get(json, "a"), "b"), "c",
                    json_object_get(json, "a"));

    if(json_dumps(json, 0))
        fail("json_dumps encoded a circular reference!");

    json_object_del(json_object_get(json_object_get(json, "a"), "b"), "c");

    result = json_dumps(json, 0);
    if(!result || strcmp(result, "{\"a\": {\"b\": {}}}"))
        fail("json_dumps failed!");
    free(result);

    json_decref(json);

    json = json_array();
    json_array_append_new(json, json_array());
    json_array_append_new(json_array_get(json, 0), json_array());
    json_array_append(json_array_get(json_array_get(json, 0), 0),
                      json_array_get(json, 0));

    if(json_dumps(json, 0))
        fail("json_dumps encoded a circular reference!");

    json_array_remove(json_array_get(json_array_get(json, 0), 0), 0);

    result = json_dumps(json, 0);
    if(!result || strcmp(result, "[[[]]]"))
        fail("json_dumps failed!");
    free(result);

    json_decref(json);
}