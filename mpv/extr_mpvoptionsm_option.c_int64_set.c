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
struct TYPE_4__ {scalar_t__ int64; } ;
struct mpv_node {scalar_t__ format; TYPE_1__ u; } ;
struct TYPE_5__ {int flags; scalar_t__ min; scalar_t__ max; } ;
typedef  TYPE_2__ m_option_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ MPV_FORMAT_INT64 ; 
 int M_OPT_MAX ; 
 int M_OPT_MIN ; 
 int M_OPT_OUT_OF_RANGE ; 
 int M_OPT_UNKNOWN ; 

__attribute__((used)) static int int64_set(const m_option_t *opt, void *dst, struct mpv_node *src)
{
    if (src->format != MPV_FORMAT_INT64)
        return M_OPT_UNKNOWN;
    int64_t val = src->u.int64;
    if ((opt->flags & M_OPT_MIN) && val < opt->min)
        return M_OPT_OUT_OF_RANGE;
    if ((opt->flags & M_OPT_MAX) && val > opt->max)
        return M_OPT_OUT_OF_RANGE;
    *(int64_t *)dst = val;
    return 1;
}