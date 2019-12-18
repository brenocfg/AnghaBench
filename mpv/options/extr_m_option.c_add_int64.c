#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; scalar_t__ min; scalar_t__ max; TYPE_1__* type; } ;
typedef  TYPE_2__ m_option_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {int size; } ;

/* Variables and functions */
 scalar_t__ INT64_MAX ; 
 scalar_t__ INT64_MIN ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ INT_MIN ; 
 int M_OPT_MAX ; 
 int M_OPT_MIN ; 

__attribute__((used)) static void add_int64(const m_option_t *opt, void *val, double add, bool wrap)
{
    int64_t v = *(int64_t *)val;

    v = v + add;

    bool is64 = opt->type->size == sizeof(int64_t);
    int64_t nmin = is64 ? INT64_MIN : INT_MIN;
    int64_t nmax = is64 ? INT64_MAX : INT_MAX;

    int64_t min = (opt->flags & M_OPT_MIN) ? opt->min : nmin;
    int64_t max = (opt->flags & M_OPT_MAX) ? opt->max : nmax;

    if (v < min)
        v = wrap ? max : min;
    if (v > max)
        v = wrap ? min : max;

    *(int64_t *)val = v;
}