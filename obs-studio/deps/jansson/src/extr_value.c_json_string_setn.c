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
 int json_string_setn_nocheck (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  utf8_check_string (char const*,size_t) ; 

int json_string_setn(json_t *json, const char *value, size_t len)
{
    if(!value || !utf8_check_string(value, len))
        return -1;

    return json_string_setn_nocheck(json, value, len);
}