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
struct TYPE_4__ {double double_; int /*<<< orphan*/  string; } ;
struct mpv_node {TYPE_1__ u; int /*<<< orphan*/  format; } ;
struct TYPE_5__ {int flags; } ;
typedef  TYPE_2__ m_option_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_FORMAT_DOUBLE ; 
 int /*<<< orphan*/  MPV_FORMAT_STRING ; 
 int M_OPT_DEFAULT_NAN ; 
 scalar_t__ isnan (double) ; 
 int /*<<< orphan*/  talloc_strdup (void*,char*) ; 

__attribute__((used)) static int double_get(const m_option_t *opt, void *ta_parent,
                      struct mpv_node *dst, void *src)
{
    double f = *(double *)src;
    if (isnan(f) && (opt->flags & M_OPT_DEFAULT_NAN)) {
        dst->format = MPV_FORMAT_STRING;
        dst->u.string = talloc_strdup(ta_parent, "default");
    } else {
        dst->format = MPV_FORMAT_DOUBLE;
        dst->u.double_ = f;
    }
    return 1;
}