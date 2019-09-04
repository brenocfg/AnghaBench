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
struct bstr {int len; char* start; } ;

/* Variables and functions */
 int bstr_sscanf (struct bstr,char*,...) ; 
 int /*<<< orphan*/  isfinite (double) ; 

__attribute__((used)) static int parse_timestring(struct bstr str, double *time, char endchar)
{
    int a, b, len;
    double d;
    *time = 0; /* ensure initialization for error cases */
    if (bstr_sscanf(str, "%d:%d:%lf%n", &a, &b, &d, &len) >= 3)
        *time = 3600 * a + 60 * b + d;
    else if (bstr_sscanf(str, "%d:%lf%n", &a, &d, &len) >= 2)
        *time = 60 * a + d;
    else if (bstr_sscanf(str, "%lf%n", &d, &len) >= 1)
        *time = d;
    else
        return 0;  /* unsupported time format */
    if (len < str.len && str.start[len] != endchar)
        return 0;  /* invalid extra characters at the end */
    if (!isfinite(*time))
        return 0;
    return len;
}