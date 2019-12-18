#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ len; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 double bstrtod (TYPE_1__,TYPE_1__*) ; 
 int /*<<< orphan*/  isfinite (double) ; 

__attribute__((used)) static bool parse_time(bstr str, double *out_time)
{
    bstr rest;
    double time = bstrtod(str, &rest);
    if (!str.len || rest.len || !isfinite(time))
        return false;
    *out_time = time;
    return true;
}