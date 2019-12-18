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
 int /*<<< orphan*/ * json_stringn_nocheck (char const*,size_t) ; 
 int /*<<< orphan*/  utf8_check_string (char const*,size_t) ; 

json_t *json_stringn(const char *value, size_t len)
{
    if(!value || !utf8_check_string(value, len))
        return NULL;

    return json_stringn_nocheck(value, len);
}