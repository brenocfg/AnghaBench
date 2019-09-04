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
 int /*<<< orphan*/  JSON_ENCODE_ANY ; 
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_stringn (char*,int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 

__attribute__((used)) static void encode_nul_byte()
{
    json_t *json;
    char *result;

    json = json_stringn("nul byte \0 in string", 20);
    result = json_dumps(json, JSON_ENCODE_ANY);
    if(!result || memcmp(result, "\"nul byte \\u0000 in string\"", 27))
        fail("json_dumps failed to dump an embedded NUL byte");

    free(result);
    json_decref(json);
}