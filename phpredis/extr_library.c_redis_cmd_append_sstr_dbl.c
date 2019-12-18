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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  smart_string ;

/* Variables and functions */
 int redis_cmd_append_sstr (int /*<<< orphan*/ *,char*,int) ; 
 int snprintf (char*,int,char*,double) ; 

int
redis_cmd_append_sstr_dbl(smart_string *str, double value)
{
    char tmp[64];
    int len, retval;

    /* Convert to string */
    len = snprintf(tmp, sizeof(tmp), "%.16g", value);

    // Append the string
    retval = redis_cmd_append_sstr(str, tmp, len);

    /* Return new length */
    return retval;
}