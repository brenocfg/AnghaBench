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
 int JSON_ALLOW_NUL ; 
 int JSON_DECODE_ANY ; 
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_is_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loads (char const*,int,int /*<<< orphan*/ *) ; 
 size_t json_string_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_string_value (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static void allow_nul()
{
    const char *text = "\"nul byte \\u0000 in string\"";
    const char *expected = "nul byte \0 in string";
    size_t len = 20;
    json_t *json;

    json = json_loads(text, JSON_ALLOW_NUL | JSON_DECODE_ANY, NULL);
    if(!json || !json_is_string(json))
        fail("unable to decode embedded NUL byte");

    if(json_string_length(json) != len)
        fail("decoder returned wrong string length");

    if(memcmp(json_string_value(json), expected, len + 1))
        fail("decoder returned wrong string content");

    json_decref(json);
}