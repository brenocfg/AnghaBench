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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_ENCODE_ANY ; 
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 scalar_t__ json_dumpf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_integer (int) ; 
 int /*<<< orphan*/ * json_string (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void encode_other_than_array_or_object()
{
    /* Encoding anything other than array or object should only
     * succeed if the JSON_ENCODE_ANY flag is used */

    json_t *json;
    FILE *fp = NULL;
    char *result;

    json = json_string("foo");
    if(json_dumps(json, 0) != NULL)
        fail("json_dumps encoded a string!");
    if(json_dumpf(json, fp, 0) == 0)
        fail("json_dumpf encoded a string!");

    result = json_dumps(json, JSON_ENCODE_ANY);
    if(!result || strcmp(result, "\"foo\"") != 0)
        fail("json_dumps failed to encode a string with JSON_ENCODE_ANY");

    free(result);
    json_decref(json);

    json = json_integer(42);
    if(json_dumps(json, 0) != NULL)
        fail("json_dumps encoded an integer!");
    if(json_dumpf(json, fp, 0) == 0)
        fail("json_dumpf encoded an integer!");

    result = json_dumps(json, JSON_ENCODE_ANY);
    if(!result || strcmp(result, "42") != 0)
        fail("json_dumps failed to encode an integer with JSON_ENCODE_ANY");

    free(result);
    json_decref(json);


}