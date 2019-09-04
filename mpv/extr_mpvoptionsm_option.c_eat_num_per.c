#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ len; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 long long INT_MAX ; 
 long long INT_MIN ; 
 scalar_t__ bstr_eatstart0 (TYPE_1__*,char*) ; 
 long long bstrtoll (TYPE_1__,TYPE_1__*,int) ; 

__attribute__((used)) static bool eat_num_per(bstr *s, int *out_num, bool *out_per)
{
    bstr rest;
    long long v = bstrtoll(*s, &rest, 10);
    if (s->len == rest.len || v < INT_MIN || v > INT_MAX)
        return false;
    *out_num = v;
    *out_per = false;
    *s = rest;
    if (bstr_eatstart0(&rest, "%") && v >= 0 && v <= 100) {
        *out_per = true;
        *s = rest;
    }
    return true;
}