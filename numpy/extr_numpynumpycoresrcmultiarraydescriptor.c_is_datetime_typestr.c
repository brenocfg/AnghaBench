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
typedef  int Py_ssize_t ;

/* Variables and functions */
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
is_datetime_typestr(char *type, Py_ssize_t len)
{
    if (len < 2) {
        return 0;
    }
    if (type[1] == '8' && (type[0] == 'M' || type[0] == 'm')) {
        return 1;
    }
    if (len < 10) {
        return 0;
    }
    if (strncmp(type, "datetime64", 10) == 0) {
        return 1;
    }
    if (len < 11) {
        return 0;
    }
    if (strncmp(type, "timedelta64", 11) == 0) {
        return 1;
    }
    return 0;
}