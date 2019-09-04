#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_3__ {char* value; size_t length; } ;
typedef  TYPE_1__ json_string_t ;

/* Variables and functions */
 int /*<<< orphan*/  json_is_string (int /*<<< orphan*/ *) ; 
 TYPE_1__* json_to_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonp_free (char*) ; 
 char* jsonp_strndup (char const*,size_t) ; 

int json_string_setn_nocheck(json_t *json, const char *value, size_t len)
{
    char *dup;
    json_string_t *string;

    if(!json_is_string(json) || !value)
        return -1;

    dup = jsonp_strndup(value, len);
    if(!dup)
        return -1;

    string = json_to_string(json);
    jsonp_free(string->value);
    string->value = dup;
    string->length = len;

    return 0;
}