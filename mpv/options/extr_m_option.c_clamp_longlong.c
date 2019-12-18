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
struct TYPE_3__ {int flags; long long max; long long min; } ;
typedef  TYPE_1__ m_option_t ;

/* Variables and functions */
 int M_OPT_MAX ; 
 int M_OPT_MIN ; 
 int M_OPT_OUT_OF_RANGE ; 

__attribute__((used)) static int clamp_longlong(const m_option_t *opt, void *val)
{
    long long v = *(long long *)val;
    int r = 0;
    if ((opt->flags & M_OPT_MAX) && (v > opt->max)) {
        v = opt->max;
        r = M_OPT_OUT_OF_RANGE;
    }
    if ((opt->flags & M_OPT_MIN) && (v < opt->min)) {
        v = opt->min;
        r = M_OPT_OUT_OF_RANGE;
    }
    *(long long *)val = v;
    return r;
}