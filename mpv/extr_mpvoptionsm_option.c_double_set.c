#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {double int64; double double_; } ;
struct mpv_node {scalar_t__ format; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  m_option_t ;

/* Variables and functions */
 scalar_t__ MPV_FORMAT_DOUBLE ; 
 scalar_t__ MPV_FORMAT_INT64 ; 
 int M_OPT_OUT_OF_RANGE ; 
 int M_OPT_UNKNOWN ; 
 scalar_t__ clamp_double (int /*<<< orphan*/  const*,double*) ; 

__attribute__((used)) static int double_set(const m_option_t *opt, void *dst, struct mpv_node *src)
{
    double val;
    if (src->format == MPV_FORMAT_INT64) {
        // Can't always be represented exactly, but don't care.
        val = src->u.int64;
    } else if (src->format == MPV_FORMAT_DOUBLE) {
        val = src->u.double_;
    } else {
        return M_OPT_UNKNOWN;
    }
    if (clamp_double(opt, &val) < 0)
        return M_OPT_OUT_OF_RANGE;
    *(double *)dst = val;
    return 1;
}