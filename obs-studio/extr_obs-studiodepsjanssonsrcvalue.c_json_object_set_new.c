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
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int json_object_set_new_nocheck (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  utf8_check_string (char const*,int /*<<< orphan*/ ) ; 

int json_object_set_new(json_t *json, const char *key, json_t *value)
{
    if(!key || !utf8_check_string(key, strlen(key)))
    {
        json_decref(value);
        return -1;
    }

    return json_object_set_new_nocheck(json, key, value);
}